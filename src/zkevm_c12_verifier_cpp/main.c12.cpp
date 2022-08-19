#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <chrono>

using json = nlohmann::json;

#include "calcwit.c12.hpp"
#include "circom.c12.hpp"

#define handle_error(msg) \
  do                      \
  {                       \
    perror(msg);          \
    exit(EXIT_FAILURE);   \
  } while (0)

Circom_CircuitC12 *loadCircuitC12(std::string const &datFileName)
{
  Circom_CircuitC12 *circuit = new Circom_CircuitC12;

  int fd;
  struct stat sb;

  fd = open(datFileName.c_str(), O_RDONLY);
  if (fd == -1)
  {
    std::cout << ".dat file not found: " << datFileName << "\n";
    throw std::system_error(errno, std::generic_category(), "open");
  }

  if (fstat(fd, &sb) == -1)
  { /* To obtain file size */
    throw std::system_error(errno, std::generic_category(), "fstat");
  }

  u8 *bdata = (u8 *)mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  close(fd);

  circuit->InputHashMap = new HashSignalInfoC12[get_size_of_input_hashmap_C12()];
  uint dsize = get_size_of_input_hashmap_C12() * sizeof(HashSignalInfoC12);
  memcpy((void *)(circuit->InputHashMap), (void *)bdata, dsize);

  circuit->witness2SignalList = new u64[get_size_of_witness_C12()];
  uint inisize = dsize;
  dsize = get_size_of_witness_C12() * sizeof(u64);
  memcpy((void *)(circuit->witness2SignalList), (void *)(bdata + inisize), dsize);

  circuit->circuitConstants = new FrElement[get_size_of_constants_C12()];
  if (get_size_of_constants_C12() > 0)
  {
    inisize += dsize;
    dsize = get_size_of_constants_C12() * sizeof(FrElement);
    memcpy((void *)(circuit->circuitConstants), (void *)(bdata + inisize), dsize);
  }

  std::map<u32, IODefPairC12> templateInsId2IOSignalInfo1;
  if (get_size_of_io_map_C12() > 0)
  {
    u32 index[get_size_of_io_map_C12()];
    inisize += dsize;
    dsize = get_size_of_io_map_C12() * sizeof(u32);
    memcpy((void *)index, (void *)(bdata + inisize), dsize);
    inisize += dsize;
    assert(inisize % sizeof(u32) == 0);
    assert(sb.st_size % sizeof(u32) == 0);
    u32 dataiomap[(sb.st_size - inisize) / sizeof(u32)];
    memcpy((void *)dataiomap, (void *)(bdata + inisize), sb.st_size - inisize);
    u32 *pu32 = dataiomap;

    for (int i = 0; i < get_size_of_io_map_C12(); i++)
    {
      u32 n = *pu32;
      IODefPairC12 p;
      p.len = n;
      IODefC12 defs[n];
      pu32 += 1;
      for (u32 j = 0; j < n; j++)
      {
        defs[j].offset = *pu32;
        u32 len = *(pu32 + 1);
        defs[j].len = len;
        defs[j].lengths = new u32[len];
        memcpy((void *)defs[j].lengths, (void *)(pu32 + 2), len * sizeof(u32));
        pu32 += len + 2;
      }
      p.defs = (IODefC12 *)calloc(10, sizeof(IODefC12));
      for (u32 j = 0; j < p.len; j++)
      {
        p.defs[j] = defs[j];
      }
      templateInsId2IOSignalInfo1[index[i]] = p;
    }
  }
  circuit->templateInsId2IOSignalInfo = move(templateInsId2IOSignalInfo1);

  munmap(bdata, sb.st_size);

  return circuit;
}

void json2FrElementsC12(json val, std::vector<FrElement> &vval)
{
  if (!val.is_array())
  {
    FrElement v;
    std::string s;
    if (val.is_string())
    {
      s = val.get<std::string>();
    }
    else if (val.is_number())
    {
      double vd = val.get<double>();
      std::stringstream stream;
      stream << std::fixed << std::setprecision(0) << vd;
      s = stream.str();
    }
    else
    {
      throw new std::runtime_error("Invalid JSON type");
    }
    Fr_str2element(&v, s.c_str());
    vval.push_back(v);
  }
  else
  {
    for (uint i = 0; i < val.size(); i++)
    {
      json2FrElementsC12(val[i], vval);
    }
  }
}

void loadJsonImplC12(Circom_CalcWitC12 *ctx, json &j)
{
  u64 nItems = j.size();
  // printf("Items : %llu\n",nItems);
  for (json::iterator it = j.begin(); it != j.end(); ++it)
  {
    // std::cout << it.key() << " => " << it.value() << '\n';
    u64 h = fnv1aC12(it.key());
    std::vector<FrElement> v;
    json2FrElementsC12(it.value(), v);
    uint signalSize = ctx->getInputSignalSize(h);
    if (v.size() < signalSize)
    {
      std::ostringstream errStrStream;
      errStrStream << "Error loading signal " << it.key() << ": Not enough values\n";
      throw std::runtime_error(errStrStream.str());
    }
    if (v.size() > signalSize)
    {
      std::ostringstream errStrStream;
      errStrStream << "Error loading signal " << it.key() << ": Too many values\n";
      throw std::runtime_error(errStrStream.str());
    }
    for (uint i = 0; i < v.size(); i++)
    {
      try
      {
        // std::cout << it.key() << "," << i << " => " << Fr_element2str(&(v[i])) << '\n';
        ctx->setInputSignal(h, i, v[i]);
      }
      catch (std::runtime_error e)
      {
        std::ostringstream errStrStream;
        errStrStream << "Error setting signal: " << it.key() << "\n"
                     << e.what();
        throw std::runtime_error(errStrStream.str());
      }
    }
  }
}

void writeBinWitnessC12(Circom_CalcWitC12 *ctx, std::string wtnsFileName)
{
  FILE *write_ptr;

  write_ptr = fopen(wtnsFileName.c_str(), "wb");

  fwrite("wtns", 4, 1, write_ptr);

  u32 version = 2;
  fwrite(&version, 4, 1, write_ptr);

  u32 nSections = 2;
  fwrite(&nSections, 4, 1, write_ptr);

  // Header
  u32 idSection1 = 1;
  fwrite(&idSection1, 4, 1, write_ptr);

  u32 n8 = Fr_N64 * 8;

  u64 idSection1length = 8 + n8;
  fwrite(&idSection1length, 8, 1, write_ptr);

  fwrite(&n8, 4, 1, write_ptr);

  fwrite(Fr_q.longVal, Fr_N64 * 8, 1, write_ptr);

  uint Nwtns = get_size_of_witness_C12();

  u32 nVars = (u32)Nwtns;
  fwrite(&nVars, 4, 1, write_ptr);

  // Data
  u32 idSection2 = 2;
  fwrite(&idSection2, 4, 1, write_ptr);

  u64 idSection2length = (u64)n8 * (u64)Nwtns;
  fwrite(&idSection2length, 8, 1, write_ptr);

  FrElement v;

  for (int i = 0; i < Nwtns; i++)
  {
    ctx->getWitness(i, &v);
    Fr_toLongNormal(&v, &v);
    fwrite(v.longVal, Fr_N64 * 8, 1, write_ptr);
  }
  fclose(write_ptr);
}

void getBinWitnessC12(Circom_CalcWitC12 *ctx, RawFr::Element *&pWitness, uint64_t &witnessSize)
{
  witnessSize = get_size_of_witness_C12();

  pWitness = (RawFr::Element *)malloc(witnessSize * sizeof(FrElement));
  if (pWitness == NULL)
  {
    std::cout << "Error: getBinWitness() failed allocating memory size: " << witnessSize << std::endl;
    exit(-1);
  }

  FrElement v;

  for (uint i = 0; i < witnessSize; i++)
  {
    ctx->getWitness(i, &v);
    Fr_toLongNormal(&v, &v);
    memcpy(pWitness + i, &v.longVal, sizeof(v.longVal));
  }
}

void loadJsonC12(Circom_CalcWitC12 *ctx, std::string filename)
{
  std::ifstream inStream(filename);
  json j;
  inStream >> j;
  inStream.close();
  loadJsonImplC12(ctx, j);
}
