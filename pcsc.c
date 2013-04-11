/*
 +----------------------------------------------------------------------+
 | PHP Version 5                                                        |
 +----------------------------------------------------------------------+
 | Copyright (c) 1997-2006 The PHP Group                                |
 +----------------------------------------------------------------------+
 | This source file is subject to version 3.01 of the PHP license,      |
 | that is bundled with this package in the file LICENSE, and is        |
 | available through the world-wide-web at the following url:           |
 | http://www.php.net/license/3_01.txt                                  |
 | If you did not receive a copy of the PHP license and are unable to   |
 | obtain it through the world-wide-web, please send a note to          |
 | license@php.net so we can mail you a copy immediately.               |
 +----------------------------------------------------------------------+
 | Author: Johannes Findeisen <you@hanez.org> - 2010                    |
 +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_pcsc.h"

#include <PCSC/winscard.h>
#include <PCSC/pcsclite.h>

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

/* {{{ pcsc_functions[]
 *
 * Every user visible function must have an entry in pcsc_functions[].
 */
zend_function_entry pcsc_functions[] = {
  PHP_FE(scard_establish_context, NULL)
  PHP_FE(scard_release_context, NULL)
  PHP_FE(scard_is_valid_context, NULL)
  PHP_FE(scard_list_readers, NULL)
  PHP_FE(scard_connect, NULL)
  //PHP_FE(scard_reconnect, NULL)
  PHP_FE(scard_disconnect, NULL)
  PHP_FE(scard_transmit, NULL)
  PHP_FE(scard_status, NULL)
  //PHP_FE(scard_cancel, NULL)
  {NULL, NULL, NULL}
};
/* }}} */

/* {{{ pcsc_module_entry
 */
zend_module_entry pcsc_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
  STANDARD_MODULE_HEADER,
#endif
  "PC/SC",
  pcsc_functions,
  PHP_MINIT(pcsc),
  PHP_MSHUTDOWN(pcsc),
  NULL,
  NULL,
  PHP_MINFO(pcsc),
#if ZEND_MODULE_API_NO >= 20010901
  "0.0.1", /* Replace with version number for your extension */
#endif
  STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PCSC
ZEND_GET_MODULE(pcsc)
#endif

#define REGISTER_PCSC_CONSTANT(__c) REGISTER_LONG_CONSTANT(#__c, __c, CONST_CS | CONST_PERSISTENT)

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(pcsc)
{
  /* Return Codes */
  REGISTER_PCSC_CONSTANT(SCARD_E_BAD_SEEK);
  REGISTER_PCSC_CONSTANT(SCARD_E_CANCELLED);
  REGISTER_PCSC_CONSTANT(SCARD_E_CANT_DISPOSE);
  REGISTER_PCSC_CONSTANT(SCARD_E_CARD_UNSUPPORTED);
  REGISTER_PCSC_CONSTANT(SCARD_E_CERTIFICATE_UNAVAILABLE);
  REGISTER_PCSC_CONSTANT(SCARD_E_COMM_DATA_LOST);
  REGISTER_PCSC_CONSTANT(SCARD_E_DIR_NOT_FOUND);
  REGISTER_PCSC_CONSTANT(SCARD_E_DUPLICATE_READER);
  REGISTER_PCSC_CONSTANT(SCARD_E_FILE_NOT_FOUND);
  REGISTER_PCSC_CONSTANT(SCARD_E_ICC_CREATEORDER);
  REGISTER_PCSC_CONSTANT(SCARD_E_ICC_INSTALLATION);
  REGISTER_PCSC_CONSTANT(SCARD_E_INSUFFICIENT_BUFFER);
  REGISTER_PCSC_CONSTANT(SCARD_E_INVALID_ATR);
  REGISTER_PCSC_CONSTANT(SCARD_E_INVALID_CHV);
  REGISTER_PCSC_CONSTANT(SCARD_E_INVALID_HANDLE);
  REGISTER_PCSC_CONSTANT(SCARD_E_INVALID_PARAMETER);
  REGISTER_PCSC_CONSTANT(SCARD_E_INVALID_TARGET);
  REGISTER_PCSC_CONSTANT(SCARD_E_INVALID_VALUE);
  REGISTER_PCSC_CONSTANT(SCARD_E_NO_ACCESS);
  REGISTER_PCSC_CONSTANT(SCARD_E_NO_DIR);
  REGISTER_PCSC_CONSTANT(SCARD_E_NO_FILE);
  REGISTER_PCSC_CONSTANT(SCARD_E_NO_KEY_CONTAINER);
  REGISTER_PCSC_CONSTANT(SCARD_E_NO_MEMORY);
  REGISTER_PCSC_CONSTANT(SCARD_E_NO_READERS_AVAILABLE);
  REGISTER_PCSC_CONSTANT(SCARD_E_NO_SERVICE);
  REGISTER_PCSC_CONSTANT(SCARD_E_NO_SMARTCARD);
  REGISTER_PCSC_CONSTANT(SCARD_E_NO_SUCH_CERTIFICATE);
  REGISTER_PCSC_CONSTANT(SCARD_E_NOT_READY);
  REGISTER_PCSC_CONSTANT(SCARD_E_NOT_TRANSACTED);
  REGISTER_PCSC_CONSTANT(SCARD_E_PCI_TOO_SMALL);
  REGISTER_PCSC_CONSTANT(SCARD_E_PROTO_MISMATCH);
  REGISTER_PCSC_CONSTANT(SCARD_E_READER_UNAVAILABLE);
  REGISTER_PCSC_CONSTANT(SCARD_E_READER_UNSUPPORTED);
  REGISTER_PCSC_CONSTANT(SCARD_E_SERVER_TOO_BUSY);
  REGISTER_PCSC_CONSTANT(SCARD_E_SERVICE_STOPPED);
  REGISTER_PCSC_CONSTANT(SCARD_E_SHARING_VIOLATION);
  REGISTER_PCSC_CONSTANT(SCARD_E_SYSTEM_CANCELLED);
  REGISTER_PCSC_CONSTANT(SCARD_E_TIMEOUT);
  REGISTER_PCSC_CONSTANT(SCARD_E_UNEXPECTED);
  REGISTER_PCSC_CONSTANT(SCARD_E_UNKNOWN_CARD);
  REGISTER_PCSC_CONSTANT(SCARD_E_UNKNOWN_READER);
  REGISTER_PCSC_CONSTANT(SCARD_E_UNKNOWN_RES_MNG);
  REGISTER_PCSC_CONSTANT(SCARD_E_UNSUPPORTED_FEATURE);
  REGISTER_PCSC_CONSTANT(SCARD_E_WRITE_TOO_MANY);
  
  REGISTER_PCSC_CONSTANT(SCARD_F_COMM_ERROR);
  REGISTER_PCSC_CONSTANT(SCARD_F_INTERNAL_ERROR);
  REGISTER_PCSC_CONSTANT(SCARD_F_UNKNOWN_ERROR);
  REGISTER_PCSC_CONSTANT(SCARD_F_WAITED_TOO_LONG);
  
  REGISTER_PCSC_CONSTANT(SCARD_P_SHUTDOWN);
  
  REGISTER_PCSC_CONSTANT(SCARD_S_SUCCESS);
  
  REGISTER_PCSC_CONSTANT(SCARD_W_CANCELLED_BY_USER);
  REGISTER_PCSC_CONSTANT(SCARD_W_CARD_NOT_AUTHENTICATED);
  REGISTER_PCSC_CONSTANT(SCARD_W_CHV_BLOCKED);
  REGISTER_PCSC_CONSTANT(SCARD_W_EOF);
  REGISTER_PCSC_CONSTANT(SCARD_W_REMOVED_CARD);
  REGISTER_PCSC_CONSTANT(SCARD_W_RESET_CARD);
  REGISTER_PCSC_CONSTANT(SCARD_W_SECURITY_VIOLATION);
  REGISTER_PCSC_CONSTANT(SCARD_W_UNPOWERED_CARD);
  REGISTER_PCSC_CONSTANT(SCARD_W_UNRESPONSIVE_CARD);
  REGISTER_PCSC_CONSTANT(SCARD_W_UNSUPPORTED_CARD);
  REGISTER_PCSC_CONSTANT(SCARD_W_WRONG_CHV);

  /* Protocols */
  REGISTER_PCSC_CONSTANT(SCARD_PROTOCOL_RAW);
  REGISTER_PCSC_CONSTANT(SCARD_PROTOCOL_T0);
  REGISTER_PCSC_CONSTANT(SCARD_PROTOCOL_T1);

  /* Disconnect Modes */
  REGISTER_PCSC_CONSTANT(SCARD_EJECT_CARD);
  REGISTER_PCSC_CONSTANT(SCARD_LEAVE_CARD);
  REGISTER_PCSC_CONSTANT(SCARD_RESET_CARD);
  REGISTER_PCSC_CONSTANT(SCARD_UNPOWER_CARD);

  /* Status codes */
  REGISTER_PCSC_CONSTANT(SCARD_ABSENT);
  REGISTER_PCSC_CONSTANT(SCARD_NEGOTIABLE);
  REGISTER_PCSC_CONSTANT(SCARD_POWERED);
  REGISTER_PCSC_CONSTANT(SCARD_PRESENT);
  REGISTER_PCSC_CONSTANT(SCARD_SPECIFIC);
  REGISTER_PCSC_CONSTANT(SCARD_SWALLOWED);
  
  return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(pcsc)
{
  return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(pcsc)
{
  php_info_print_table_start();
  php_info_print_table_header(2, "PC/SC support", "enabled");
  php_info_print_table_end();
}
/* }}} */

static char *e_bytes_to_hex(BYTE *buffer, DWORD length)
{
  DWORD i;
  char tmp[3];
  char *str;

  str = emalloc(2 * length + 1);
  str[0] = '\0';

  for (i = 0; i < length; i++) {
    sprintf(tmp, "%02X", buffer[i]);
    strcat(str, tmp);
  }
  return str;
}

static BYTE hex_to_nibble(char chr)
{
  if ((chr >= '0') && (chr <= '9')) {
    return chr - '0';
  }
  if ((chr >= 'A') && (chr <= 'F')) {
    return chr - 'A' + 10;
  }
  if ((chr >= 'a') && (chr <= 'f')) {
    return chr - 'a' + 10;
  }
  return 0;
}

static BYTE hex_to_byte(char *str)
{
  return hex_to_nibble(str[0]) * 0x10 + hex_to_nibble(str[1]);
}

static BYTE *e_hex_to_bytes(char *str, DWORD *length)
{
  DWORD i, l;
  BYTE *buf;

  if (str == NULL) { 
    return NULL;
  }
  
  l = strlen(str) / 2;
  if (length != NULL) {
    *length = l;
  }
  
  buf = emalloc(l);

  for (i = 0; i < l; i++) {
    buf[i] = hex_to_byte(&str[2 * i]);
  }
  return buf;
}

/* {{{ proto array pcsc_establishcontext()
   Return a a context to the PC/SC layer */
PHP_FUNCTION(scard_establish_context)
{
  /* TODO: Make the use of SCARDCONTEXT for the context everywhere instead of LONG */
  SCARDCONTEXT scard_context = 0;
  LONG rc = 0;

  rc = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &scard_context);
  if (rc != SCARD_S_SUCCESS)
  {
    RETURN_FALSE;
  }
  RETURN_LONG(scard_context);
}
/* }}} */

/* {{{ proto boolean scard_is_valid_context(long context)
   Return a a context to the PC/SC layer */
PHP_FUNCTION(scard_is_valid_context)
{
  LONG rc = 0;
  LONG *context;
  
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &context) == FAILURE) {
    return;
  }
  
  rc = SCardIsValidContext(context);
  if (rc != SCARD_S_SUCCESS) {
    RETURN_FALSE;
  }
  RETURN_TRUE;
}
/* }}} */

/* {{{ proto array pcsc_establishcontext(long context)
   Return a a context to the PC/SC layer */
PHP_FUNCTION(scard_release_context)
{
  LONG rc = 0;
  LONG *context;
  
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &context) == FAILURE) {
    return;
  }

  rc = SCardIsValidContext(context);
  if (rc != SCARD_S_SUCCESS) {
    RETURN_FALSE;
  }

  rc = SCardReleaseContext(context);
  if (rc != SCARD_S_SUCCESS) {
    RETURN_FALSE;
  }
  RETURN_LONG(context);
}
/* }}} */

/* {{{ proto array pcsc_listreaders(long context)
   Return a an array of available PC/SC readers */
PHP_FUNCTION(scard_list_readers)
{
  char *strReaders = NULL;
  char *ptrReader;
  DWORD dwLen = SCARD_AUTOALLOCATE;
  LONG rc = 0;
  LONG *context;
  
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &context) == FAILURE) {
    return;
  }
  
  rc = SCardIsValidContext(context);
  if (rc != SCARD_S_SUCCESS) {
    RETURN_FALSE;
  }
  
  rc = SCardListReaders(context, NULL, (char *) &strReaders, &dwLen);
  if (rc != SCARD_S_SUCCESS) {
    RETURN_FALSE;
  }
  
  if (strReaders == NULL) {
    RETURN_FALSE;
  }
  
  array_init(return_value);

  ptrReader = strReaders;
  do {
    add_next_index_string(return_value, ptrReader, TRUE);
    ptrReader+= strlen(ptrReader);
    ptrReader++;
  } while (*ptrReader != '\0');
  
  SCardFreeMemory(context, strReaders);
}
/* }}} */

/* {{{ proto long scardconnect(long context, string reader_name, [long preferred_protocol], [long &current_protocol])
   Return a handle to the card */
   /* TODO: Add support for the protocol parameters; default is "T=1" now and not changeable */
PHP_FUNCTION(scard_connect)
{
  DWORD dwPreferredProtocol = SCARD_PROTOCOL_T1; 
  DWORD dwCurrentProtocol;
  SCARDHANDLE hCard = 0;
  LONG rc = 0;
  LONG *context;
  char *strReaderName;
  int strReaderNameLen;
  
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ls", &context, &strReaderName, &strReaderNameLen) == FAILURE) {
    return;
  }
  
  rc = SCardIsValidContext(context);
  if (rc != SCARD_S_SUCCESS) {
    RETURN_FALSE;
  }

  rc = SCardConnect(context, strReaderName, SCARD_SHARE_SHARED, dwPreferredProtocol, &hCard, &dwCurrentProtocol);
  if (rc != SCARD_S_SUCCESS) {
    RETURN_FALSE;
  }

  RETURN_LONG(hCard);
}
/* }}} */

/* {{{ proto boolean scarddisconnect(long card_handle, [long disposition])
   Close a card connection obtained with scardconnect */
   /* TODO: Add support for disposition. */
PHP_FUNCTION(scard_disconnect)
{
  DWORD dwDisposition = SCARD_EJECT_CARD;
  LONG rc;
  SCARDHANDLE *hCard;
  
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &hCard) == FAILURE) {
    return;
  }

  /*if (argc >= 2) {
    convert_to_long(ARG(1));
    dwDisposition = ARG(1)->value.lval;
  }*/
  
  rc = SCardDisconnect(hCard, dwDisposition);
  if (rc != SCARD_S_SUCCESS) {
    RETURN_FALSE;
  }
  RETURN_TRUE;
}
/* }}} */

/* {{{ proto string scardtransmit(long card_handle, string send_command)
   Transmit (and receive) data to (and from) the card */
PHP_FUNCTION(scard_transmit)
{
  SCARDHANDLE hCard;
  DWORD dwProtocol;
  DWORD dwState;
  const SCARD_IO_REQUEST *sendPci = NULL;
  SCARD_IO_REQUEST *recvPci = NULL;
  BYTE *sendBuffer;
  BYTE *recvBuffer;
  DWORD sendLen, recvLen;
  LONG rc;
  char *apdu;
  int apduLen;
  
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ls", &hCard, &apdu, &apduLen) == FAILURE) {
    return;
  }

  /* Are we in T=0 or T=1 ? */
  rc = SCardStatus(hCard, NULL, NULL, &dwState, &dwProtocol, NULL, NULL);
  if (rc != SCARD_S_SUCCESS) {
    RETURN_FALSE;
  }
        
  if (!(dwState & SCARD_POWERED)) {
    RETURN_FALSE;
  }
  
  switch (dwProtocol) {
    case SCARD_PROTOCOL_RAW : sendPci = SCARD_PCI_RAW; break;
    case SCARD_PROTOCOL_T0  : sendPci = SCARD_PCI_T0;  break;
    case SCARD_PROTOCOL_T1  : sendPci = SCARD_PCI_T1;  break;
  }

  /* Get buffer to send */
  sendBuffer = e_hex_to_bytes(apdu, &sendLen);

  /* Guess the size of the buffer to recv */
  recvLen    = 2 + 256;
  recvBuffer = emalloc(recvLen);

  /* Perform the exchange */
  recvPci = emalloc(1024);
  recvPci->dwProtocol  = dwProtocol;
  recvPci->cbPciLength = 1024;

  rc = SCardTransmit(hCard, sendPci, sendBuffer, sendLen, recvPci, recvBuffer, &recvLen);
  if (rc != SCARD_S_SUCCESS) {
    efree(recvPci);
    efree(recvBuffer);
    efree(sendBuffer);
    RETURN_FALSE;
  }
  efree(recvPci);

  /* Return the response */
  RETVAL_STRING(e_bytes_to_hex(recvBuffer, recvLen), TRUE);

  /* Free local data */
  efree(recvBuffer);
  efree(sendBuffer);
}
/* }}} */

/* {{{ proto array scardstatus([long card_handle])
   Retrieve reader's or card's status */
PHP_FUNCTION(scard_status)
{
  SCARDHANDLE hCard = 0;
  char *strReader = NULL;
  DWORD dwProtocol, dwState;
  BYTE atrBuffer[32];
  DWORD atrLen;
  LONG rc;
  
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &hCard) == FAILURE) {
    return;
  }

  atrLen = sizeof(atrBuffer);
  rc = SCardStatus(hCard, NULL, NULL, &dwState, &dwProtocol, atrBuffer, &atrLen);
  if (rc != SCARD_S_SUCCESS) {
    RETURN_FALSE;
  }

  array_init(return_value);
  add_assoc_long(return_value, "state",    dwState);
  if (dwState & SCARD_ABSENT)
    add_assoc_long(return_value, "SCARD_ABSENT", 1);

  if (dwState & SCARD_PRESENT)
    add_assoc_long(return_value, "SCARD_PRESENT", 1);

  if (dwState & SCARD_SWALLOWED)
    add_assoc_long(return_value, "SCARD_SWALLOWED", 1);

  if (dwState & SCARD_POWERED)
    add_assoc_long(return_value, "SCARD_POWERED", 1);

  if (dwState & SCARD_NEGOTIABLE)
    add_assoc_long(return_value, "SCARD_NEGOTIABLE", 1);

  if (dwState & SCARD_SPECIFIC)
    add_assoc_long(return_value, "SCARD_SPECIFIC", 1);

  switch (dwProtocol) {
    /* Maybe change to bool type here instead of add_assoc_long...? */
    case SCARD_PROTOCOL_RAW : add_assoc_long(return_value, "SCARD_PROTOCOL_RAW", 1);
                              add_assoc_string(return_value, "PROTOCOL", "RAW", TRUE);
                              break;
    case SCARD_PROTOCOL_T0  : add_assoc_long(return_value, "SCARD_PROTOCOL_T0", 1);
                              add_assoc_string(return_value, "PROTOCOL", "T=0", TRUE);
                              break;
    case SCARD_PROTOCOL_T1  : add_assoc_long(return_value, "SCARD_PROTOCOL_T1", 1);
                              add_assoc_string(return_value, "PROTOCOL", "T=1", TRUE);
                              break;
    default                 : add_assoc_long(return_value, "PROTOCOL", dwProtocol);
  }

  if (atrLen) {
    char *atrString;
    atrString = e_bytes_to_hex(atrBuffer, atrLen);
    add_assoc_string(return_value, "ATR", atrString, TRUE);
    efree(atrString);
  }
}
/* }}} */
