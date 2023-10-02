#include "key_value_page.hpp"
#include "zklog.hpp"
#include "exit_process.hpp"
#include "zkassert.hpp"
#include "scalar.hpp"
#include "page_manager.hpp"
#include "hash_page.hpp"

zkresult KeyValuePage::InitEmptyPage (const uint64_t pageNumber)
{
    return ZKR_SUCCESS;
}

zkresult KeyValuePage::Read (const uint64_t pageNumber, const string &key, const string &keyBits, mpz_class &value, const uint64_t level)
{
    zkassert(key.size() == 32);
    zkassert(keyBits.size() == 42);
    zkassert(level < 42);

    // Get the data from this page
    KeyValueStruct * page = (KeyValueStruct *)pageManager.getPage(pageNumber);
    uint64_t hashPage1Number = page->hashPage1AndHistoryCounter & 0xFFFFFF;
    uint64_t historyCounter = page->hashPage1AndHistoryCounter >> 48;
    uint64_t hashPage2Number = page->hashPage2AndPadding & 0xFFFFFF;

    uint8_t levelBits = key[level];
    uint8_t * keyValueEntry = page->keyValueEntry[levelBits];
    uint64_t entryPageNumber = (*(uint64_t *)keyValueEntry) & 0xFFFFFF;
    uint64_t control = (*(uint64_t *)keyValueEntry) >> 48;
    uint64_t version = (*(uint64_t *)(keyValueEntry + 8)) & 0xFFFFFF;
    uint64_t previousVersionOffset = (*(uint64_t *)(keyValueEntry + 8)) >> 48;

    // Check control
    switch (control)
    {
        // Empty slot
        case 0:
        {
            value = 0;
            return ZKR_SUCCESS;            
        }
        // Leaf node
        case 1:
        {

        }
        // Intermediate node
        case 2:
        {
            return Read(pageNumber, key, keyBits, value, level + 1);
        }
        default:
        {
            zklog.error("KeyValuePage::Write() found invalid control=" + to_string(control) + " pageNumber=" + to_string(pageNumber));
            return ZKR_DB_ERROR;
        }
    }

    // Not found
    return ZKR_DB_KEY_NOT_FOUND;
}

zkresult KeyValuePage::Read (const uint64_t pageNumber, const string &key, mpz_class &value)
{
    zkassert(key.size() == 32);

    // TODO: split the key in 256/6=42 bytes, and pass it to the other Read() method
    string keyBits;

    return Read(pageNumber, key, keyBits, value, 0);
}

zkresult KeyValuePage::Write (uint64_t &pageNumber, const string &key, const string &keyBits, const mpz_class &value, const uint64_t level)
{
    zkassert(key.size() == 32);
    zkassert(keyBits.size() == 42);
    zkassert(level < 42);

    // Get the data from this page
    KeyValueStruct * page = (KeyValueStruct *)pageManager.getPage(pageNumber);
    uint64_t hashPage1Number = page->hashPage1AndHistoryCounter & 0xFFFFFF;
    uint64_t historyCounter = page->hashPage1AndHistoryCounter >> 48;
    uint64_t hashPage2Number = page->hashPage2AndPadding & 0xFFFFFF;

    uint8_t levelBits = key[level];
    uint8_t * keyValueEntry = page->keyValueEntry[levelBits];
    uint64_t entryPageNumber = (*(uint64_t *)keyValueEntry) & 0xFFFFFF;
    uint64_t control = (*(uint64_t *)keyValueEntry) >> 48;
    uint64_t version = (*(uint64_t *)(keyValueEntry + 8)) & 0xFFFFFF;
    uint64_t previousVersionOffset = (*(uint64_t *)(keyValueEntry + 8)) >> 48;

    // Check control
    switch (control)
    {
        // Empty slot
        case 0:
        {

            
        }
        // Leaf node
        case 1:
        {

        }
        // Intermediate node
        case 2:
        {
            return Write(pageNumber, key, keyBits, value, level + 1);
        }
        default:
        {
            zklog.error("KeyValuePage::Write() found invalid control=" + to_string(control) + " pageNumber=" + to_string(pageNumber));
            return ZKR_DB_ERROR;
        }
    }
}

zkresult KeyValuePage::Write (uint64_t &pageNumber, const string &key, const mpz_class &value)
{
    zkassert(key.size() == 32);

    // TODO: split the key in 256/6=42 bytes, and pass it to the other Write() method
    string keyBits;

    // Start searching with level 0
    return Write(pageNumber, key, keyBits, value, 0);
}


void KeyValuePage::Print (const uint64_t pageNumber, bool details)
{
    zklog.info("KeyValuePage::Print() pageNumber=" + to_string(pageNumber));

    // Get the data from this page
    KeyValueStruct * page = (KeyValueStruct *)pageManager.getPage(pageNumber);
    uint64_t hashPage1Number = page->hashPage1AndHistoryCounter & 0xFFFFFF;
    uint64_t historyCounter = page->hashPage1AndHistoryCounter >> 48;
    uint64_t hashPage2Number = page->hashPage2AndPadding & 0xFFFFFF;
    zklog.info("  hashPage1Number=" + to_string(hashPage1Number));
    HashPage::Print(hashPage1Number, details);
    zklog.info("  hashPage2Number=" + to_string(hashPage2Number));
    HashPage::Print(hashPage2Number, details);
    zklog.info("  historyCounter=" + to_string(historyCounter));

    for (uint64_t i=0; i<64; i++)
    {
        uint8_t * keyValueEntry = page->keyValueEntry[i];
        uint64_t entryPageNumber = (*(uint64_t *)keyValueEntry) & 0xFFFFFF;
        uint64_t control = (*(uint64_t *)keyValueEntry) >> 48;
        uint64_t version = (*(uint64_t *)(keyValueEntry + 8)) & 0xFFFFFF;
        uint64_t previousVersionOffset = (*(uint64_t *)(keyValueEntry + 8)) >> 48;

        // Check control
        switch (control)
        {
            // Empty slot
            case 0:
            {
                continue;                
            }
            // Leaf node
            case 1:
            {

            }
            // Intermediate node
            case 2:
            {

            }
            default:
            {
                zklog.error("KeyValuePage::Print() found invalid control=" + to_string(control) + " pageNumber=" + to_string(pageNumber));
                exitProcess();
            }
        }
    }
}