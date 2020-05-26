#include "NDefLib/Message.h"
#include "NDefLib/NDefNfcTag.h"
#include "NDefLib/RecordType/RecordText.h"
#include "NDefLib/RecordType/RecordURI.h"
#include "mbed.h"

/**
 * Chain of callback that will read a NDef Message and print all the
 * record of type URI.
 * After each operation the class will switch on a led
 */
class ReadCallbacks : public NDefLib::NDefNfcTag::Callbacks {

  DigitalOut &mOnOpenSession;
  DigitalOut &mOnRead;
  DigitalOut &mOnCloseSession;
  const size_t buf_size = 128;
  char *buf = new char[buf_size];
  NDefLib::Message readmMsg;
  // NDefLib::Message *writemMsg;

public:
  /**
   * create the callback chain
   * @param onOpenSession led to switch on when the session open
   * @param onWrite led to switch on when the write end
   * @param onCloseSession led to switch on when the session end
   */
  ReadCallbacks(DigitalOut &onOpenSession, DigitalOut &onRead,
                DigitalOut &onCloseSession)
      : mOnOpenSession(onOpenSession), mOnRead(onRead),
        mOnCloseSession(onCloseSession){};

  /**
   * crate the new message and write it
   * @param tag tag where write the message
   * @param success true if the session correctly open
   */
  virtual void on_session_open(NDefLib::NDefNfcTag *tag, bool success) {
    if (!success) {
      printf("Error opening the session\r\n");
    } // else
    printf("NFC session opened\r\n");
    // ask to have an interrupt when the command finish
    mOnOpenSession = 1;
    mOnCloseSession = 0;
    tag->read(&readmMsg);
  }

  /**
   * request to close the session
   * @param tag tag where close the session
   * @param success true if the message is correctly wrote
   * @param message wrote
   */
  virtual void on_message_read(NDefLib::NDefNfcTag *tag, bool success,
                               const NDefLib::Message *) {

    if (!success) {
      printf("Error Reading tag!\r\n");
    } else {
      const uint32_t nRecords = readmMsg.get_N_records();
      if (nRecords == 0) {
        exit(-1);
      }
      printf("Read %d record(s)!\r\n", nRecords);
      for (uint32_t i = 0; i < nRecords; i++) {
        if (readmMsg[i]->get_type() == NDefLib::Record::TYPE_URI) {
          NDefLib::RecordURI *rUri = (NDefLib::RecordURI *)readmMsg[i];
          printf("UriType: %x\r\nUriContent: %s\r\n", rUri->get_uri_id(),
                 rUri->get_content().c_str());
        } else if (readmMsg[i]->get_type() == NDefLib::Record::TYPE_TEXT) {
          NDefLib::RecordText *rText = (NDefLib::RecordText *)readmMsg[i];
          int ret = snprintf(buf, buf_size, "%s", rText->get_text().c_str());
          if (ret < 0) {
            printf("ERROR: snprintf() returns %d.", ret);
            continue;
          }
          printf("Text: %s\r\n", buf);
        } else {
          printf("Other Type\r\n");
        } // if
      }   // for
      NDefLib::Message::remove_and_delete_all_record(readmMsg);
      mOnRead = 1;
    } // if-else
    tag->close_session();
  }

  /**
   * switch on the led
   * @param tag where the session is closed
   * @param success true if the session is correctly close
   */
  virtual void on_session_close(NDefLib::NDefNfcTag *, bool success) {
    if (success) {
      printf("NFC session closed\r\n");
      mOnCloseSession = 1;
      mOnOpenSession = 0;
      mOnRead = 0;
    } else {
      printf("Error closing the session\r\n");
    }
  }

  /*
virtual void on_message_write(NDefLib::NDefNfcTag *tag, bool success) {

  if (!success) {
    printf("Error writing tag!\r\n");
  } else {
    printf("Tag written!\r\n");
    mOnCloseSession = 1;
  } // if-else

  NDefLib::Message::remove_and_delete_all_record(*writemMsg);
  delete writemMsg;
  tag->close_session();
}
*/
  /**
   * return the message
   */
  const char *get_string() { return buf; }
};