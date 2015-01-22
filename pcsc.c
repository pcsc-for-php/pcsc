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

ZEND_DECLARE_MODULE_GLOBALS(pcsc);


#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

/* arg info for scard_connect (accepts an optional compile-time reference parameter) */
ZEND_BEGIN_ARG_INFO_EX(php_pcsc_scard_connect_arginfo,0,0,2)
	ZEND_ARG_INFO(0,context)
	ZEND_ARG_INFO(0,reader_name)
	ZEND_ARG_INFO(0,preferred_protocol)
	ZEND_ARG_INFO(1,active_protocol)
ZEND_END_ARG_INFO()

/* {{{ pcsc_functions[]
 *
 * Every user visible function must have an entry in pcsc_functions[].
 */
zend_function_entry pcsc_functions[] = {
  PHP_FE(scard_establish_context, NULL)
  PHP_FE(scard_release_context, NULL)
  PHP_FE(scard_is_valid_context, NULL)
  PHP_FE(scard_list_readers, NULL)
  PHP_FE(scard_connect, php_pcsc_scard_connect_arginfo)
  //PHP_FE(scard_reconnect, NULL)
  PHP_FE(scard_disconnect, NULL)
  PHP_FE(scard_transmit, NULL)
  PHP_FE(scard_status, NULL)
  PHP_FE(scard_last_errno, NULL)
  PHP_FE(scard_errstr, NULL)
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
  PHP_PCSC_VERSION,
#endif
  STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PCSC
ZEND_GET_MODULE(pcsc)
#endif

#define REGISTER_PCSC_CONSTANT(__c) REGISTER_LONG_CONSTANT(#__c, __c, CONST_CS | CONST_PERSISTENT)

/* resource container: context */
static int le_pcsc_ctx_res;
static void php_pcsc_ctx_res_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC) {
	SCARDCONTEXT context;
	LONG rc=0;
	
	context=(SCARDCONTEXT)rsrc->ptr;
	rc = SCardIsValidContext(context);
	if (rc != SCARD_S_SUCCESS) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "PC/SC context dtor: SCardIsValidContext returned %s (0x%x)",php_pcsc_error_to_string(rc),rc);
		return;
	}

	rc = SCardReleaseContext(context);
	if (rc != SCARD_S_SUCCESS) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "PC/SC context dtor: SCardReleaseContext returned %s (0x%x)",php_pcsc_error_to_string(rc),rc);
		return;
	}
	return;
}

/* resource container: connection */
static int le_pcsc_conn_res;
static void php_pcsc_conn_res_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC) {
	SCARDHANDLE hCard;
	LONG rc;

	//TODO: actually use this
	return;
	php_printf("conn dtor\n");
	hCard=(SCARDHANDLE)rsrc->ptr;
	
	rc = SCardDisconnect(hCard, SCARD_LEAVE_CARD);
	if (rc != SCARD_S_SUCCESS) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "PC/SC connection dtor: SCardDisconnect returned %s (0x%x)",php_pcsc_error_to_string(rc),rc);
	}
}

/* TLS */
static void php_pcsc_globals_ctor(zend_pcsc_globals* pcsc_globals) {
	pcsc_globals->last_errno=SCARD_S_SUCCESS;
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(pcsc)
{
  /* Return Codes */
#ifdef SCARD_E_BAD_SEEK
  REGISTER_PCSC_CONSTANT(SCARD_E_BAD_SEEK);
#endif
  REGISTER_PCSC_CONSTANT(SCARD_E_CANCELLED);
  REGISTER_PCSC_CONSTANT(SCARD_E_CANT_DISPOSE);
  REGISTER_PCSC_CONSTANT(SCARD_E_CARD_UNSUPPORTED);
#ifdef SCARD_E_CERTIFICATE_UNAVAILABLE
  REGISTER_PCSC_CONSTANT(SCARD_E_CERTIFICATE_UNAVAILABLE);
#endif
#ifdef SCARD_E_COMM_DATA_LOST
  REGISTER_PCSC_CONSTANT(SCARD_E_COMM_DATA_LOST);
#endif
#ifdef SCARD_E_DIR_NOT_FOUND
  REGISTER_PCSC_CONSTANT(SCARD_E_DIR_NOT_FOUND);
#endif
  REGISTER_PCSC_CONSTANT(SCARD_E_DUPLICATE_READER);
#ifdef SCARD_E_FILE_NOT_FOUND
  REGISTER_PCSC_CONSTANT(SCARD_E_FILE_NOT_FOUND);
#endif
#ifdef SCARD_E_ICC_CREATEORDER
  REGISTER_PCSC_CONSTANT(SCARD_E_ICC_CREATEORDER);
#endif
#ifdef SCARD_E_ICC_INSTALLATION
  REGISTER_PCSC_CONSTANT(SCARD_E_ICC_INSTALLATION);
#endif
  REGISTER_PCSC_CONSTANT(SCARD_E_INSUFFICIENT_BUFFER);
  REGISTER_PCSC_CONSTANT(SCARD_E_INVALID_ATR);
#ifdef SCARD_E_INVALID_CHV
  REGISTER_PCSC_CONSTANT(SCARD_E_INVALID_CHV);
#endif
  REGISTER_PCSC_CONSTANT(SCARD_E_INVALID_HANDLE);
  REGISTER_PCSC_CONSTANT(SCARD_E_INVALID_PARAMETER);
  REGISTER_PCSC_CONSTANT(SCARD_E_INVALID_TARGET);
  REGISTER_PCSC_CONSTANT(SCARD_E_INVALID_VALUE);
#ifdef SCARD_E_NO_ACCESS
  REGISTER_PCSC_CONSTANT(SCARD_E_NO_ACCESS);
#endif
#ifdef SCARD_E_NO_DIR
  REGISTER_PCSC_CONSTANT(SCARD_E_NO_DIR);
#endif
#ifdef SCARD_E_NO_FILE
  REGISTER_PCSC_CONSTANT(SCARD_E_NO_FILE);
#endif
#ifdef SCARD_E_NO_KEY_CONTAINER
  REGISTER_PCSC_CONSTANT(SCARD_E_NO_KEY_CONTAINER);
#endif
  REGISTER_PCSC_CONSTANT(SCARD_E_NO_MEMORY);
  REGISTER_PCSC_CONSTANT(SCARD_E_NO_READERS_AVAILABLE);
  REGISTER_PCSC_CONSTANT(SCARD_E_NO_SERVICE);
  REGISTER_PCSC_CONSTANT(SCARD_E_NO_SMARTCARD);
#ifdef SCARD_E_NO_SUCH_CERTIFICATE
  REGISTER_PCSC_CONSTANT(SCARD_E_NO_SUCH_CERTIFICATE);
#endif
  REGISTER_PCSC_CONSTANT(SCARD_E_NOT_READY);
  REGISTER_PCSC_CONSTANT(SCARD_E_NOT_TRANSACTED);
  REGISTER_PCSC_CONSTANT(SCARD_E_PCI_TOO_SMALL);
  REGISTER_PCSC_CONSTANT(SCARD_E_PROTO_MISMATCH);
  REGISTER_PCSC_CONSTANT(SCARD_E_READER_UNAVAILABLE);
  REGISTER_PCSC_CONSTANT(SCARD_E_READER_UNSUPPORTED);
#ifdef SCARD_E_SERVER_TOO_BUSY
  REGISTER_PCSC_CONSTANT(SCARD_E_SERVER_TOO_BUSY);
#endif
  REGISTER_PCSC_CONSTANT(SCARD_E_SERVICE_STOPPED);
  REGISTER_PCSC_CONSTANT(SCARD_E_SHARING_VIOLATION);
  REGISTER_PCSC_CONSTANT(SCARD_E_SYSTEM_CANCELLED);
  REGISTER_PCSC_CONSTANT(SCARD_E_TIMEOUT);
#ifdef SCARD_E_UNEXPECTED
  REGISTER_PCSC_CONSTANT(SCARD_E_UNEXPECTED);
#endif
  REGISTER_PCSC_CONSTANT(SCARD_E_UNKNOWN_CARD);
  REGISTER_PCSC_CONSTANT(SCARD_E_UNKNOWN_READER);
#ifdef SCARD_E_UNKNOWN_RES_MNG
  REGISTER_PCSC_CONSTANT(SCARD_E_UNKNOWN_RES_MNG);
#endif
  REGISTER_PCSC_CONSTANT(SCARD_E_UNSUPPORTED_FEATURE);
#ifdef SCARD_E_WRITE_TOO_MANY
  REGISTER_PCSC_CONSTANT(SCARD_E_WRITE_TOO_MANY);
#endif
  
  REGISTER_PCSC_CONSTANT(SCARD_F_COMM_ERROR);
  REGISTER_PCSC_CONSTANT(SCARD_F_INTERNAL_ERROR);
  REGISTER_PCSC_CONSTANT(SCARD_F_UNKNOWN_ERROR);
  REGISTER_PCSC_CONSTANT(SCARD_F_WAITED_TOO_LONG);
  
#ifdef SCARD_P_SHUTDOWN
  REGISTER_PCSC_CONSTANT(SCARD_P_SHUTDOWN);
#endif
  
  REGISTER_PCSC_CONSTANT(SCARD_S_SUCCESS);
  
#ifdef SCARD_W_CANCELLED_BY_USER
  REGISTER_PCSC_CONSTANT(SCARD_W_CANCELLED_BY_USER);
#endif
#ifdef SCARD_W_CARD_NOT_AUTHENTICATED
  REGISTER_PCSC_CONSTANT(SCARD_W_CARD_NOT_AUTHENTICATED);
#endif
#ifdef SCARD_W_CHV_BLOCKED
  REGISTER_PCSC_CONSTANT(SCARD_W_CHV_BLOCKED);
#endif
#ifdef SCARD_W_EOF
  REGISTER_PCSC_CONSTANT(SCARD_W_EOF);
#endif
  REGISTER_PCSC_CONSTANT(SCARD_W_REMOVED_CARD);
  REGISTER_PCSC_CONSTANT(SCARD_W_RESET_CARD);
#ifdef SCARD_W_SECURITY_VIOLATION
  REGISTER_PCSC_CONSTANT(SCARD_W_SECURITY_VIOLATION);
#endif
  REGISTER_PCSC_CONSTANT(SCARD_W_UNPOWERED_CARD);
  REGISTER_PCSC_CONSTANT(SCARD_W_UNRESPONSIVE_CARD);
  REGISTER_PCSC_CONSTANT(SCARD_W_UNSUPPORTED_CARD);
#ifdef SCARD_W_WRONG_CHV
  REGISTER_PCSC_CONSTANT(SCARD_W_WRONG_CHV);
#endif

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

  /* resource containers */
  le_pcsc_ctx_res=zend_register_list_destructors_ex(php_pcsc_ctx_res_dtor, NULL, PHP_PCSC_CTX_RES_NAME,module_number);
  le_pcsc_conn_res=zend_register_list_destructors_ex(php_pcsc_conn_res_dtor, NULL, PHP_PCSC_CONN_RES_NAME,module_number);

  /* TLS */
  #ifdef ZTS
  ts_allocate_id(&pcsc_globals_id,sizeof(zend_pcsc_globals),(ts_allocate_ctor)php_pcsc_globals_ctor, NULL);
  #else
  php_pcsc_globals_ctor(&pcsc_globals TSRMLS_CC);
  #endif

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

/* map error codes to string */
static char* php_pcsc_error_to_string(DWORD dwRC) {
	switch(dwRC) {
#ifdef SCARD_E_BAD_SEEK
		case SCARD_E_BAD_SEEK: return "SCARD_E_BAD_SEEK";
#endif
		case SCARD_E_CANCELLED: return "SCARD_E_CANCELLED";
		case SCARD_E_CANT_DISPOSE: return "SCARD_E_CANT_DISPOSE";
		case SCARD_E_CARD_UNSUPPORTED: return "SCARD_E_CARD_UNSUPPORTED";
#ifdef SCARD_E_CERTIFICATE_UNAVAILABLE
		case SCARD_E_CERTIFICATE_UNAVAILABLE: return "SCARD_E_CERTIFICATE_UNAVAILABLE";
#endif
#ifdef SCARD_E_COMM_DATA_LOST
		case SCARD_E_COMM_DATA_LOST: return "SCARD_E_COMM_DATA_LOST";
#endif
#ifdef SCARD_E_DIR_NOT_FOUND
		case SCARD_E_DIR_NOT_FOUND: return "SCARD_E_DIR_NOT_FOUND";
#endif
		case SCARD_E_DUPLICATE_READER: return "SCARD_E_DUPLICATE_READER";
#ifdef SCARD_E_FILE_NOT_FOUND
		case SCARD_E_FILE_NOT_FOUND: return "SCARD_E_FILE_NOT_FOUND";
#endif
#ifdef SCARD_E_ICC_CREATEORDER
		case SCARD_E_ICC_CREATEORDER: return "SCARD_E_ICC_CREATEORDER";
#endif
#ifdef SCARD_E_ICC_INSTALLATION
		case SCARD_E_ICC_INSTALLATION: return "SCARD_E_ICC_INSTALLATION";
#endif
		case SCARD_E_INSUFFICIENT_BUFFER: return "SCARD_E_INSUFFICIENT_BUFFER";
		case SCARD_E_INVALID_ATR: return "SCARD_E_INVALID_ATR";
#ifdef SCARD_E_INVALID_CHV
		case SCARD_E_INVALID_CHV: return "SCARD_E_INVALID_CHV";
#endif
		case SCARD_E_INVALID_HANDLE: return "SCARD_E_INVALID_HANDLE";
		case SCARD_E_INVALID_PARAMETER: return "SCARD_E_INVALID_PARAMETER";
		case SCARD_E_INVALID_TARGET: return "SCARD_E_INVALID_TARGET";
		case SCARD_E_INVALID_VALUE: return "SCARD_E_INVALID_VALUE";
#ifdef SCARD_E_NO_ACCESS
		case SCARD_E_NO_ACCESS: return "SCARD_E_NO_ACCESS";
#endif
#ifdef SCARD_E_NO_DIR
		case SCARD_E_NO_DIR: return "SCARD_E_NO_DIR";
#endif
#ifdef SCARD_E_NO_FILE
		case SCARD_E_NO_FILE: return "SCARD_E_NO_FILE";
#endif
#ifdef SCARD_E_NO_KEY_CONTAINER
		case SCARD_E_NO_KEY_CONTAINER: return "SCARD_E_NO_KEY_CONTAINER";
#endif
		case SCARD_E_NO_MEMORY: return "SCARD_E_NO_MEMORY";
		case SCARD_E_NO_READERS_AVAILABLE: return "SCARD_E_NO_READERS_AVAILABLE";
		case SCARD_E_NO_SERVICE: return "SCARD_E_NO_SERVICE";
		case SCARD_E_NO_SMARTCARD: return "SCARD_E_NO_SMARTCARD";
#ifdef SCARD_E_NO_ACCESS
		case SCARD_E_NO_SUCH_CERTIFICATE: return "SCARD_E_NO_SUCH_CERTIFICATE";
#endif
		case SCARD_E_NOT_READY: return "SCARD_E_NOT_READY";
		case SCARD_E_NOT_TRANSACTED: return "SCARD_E_NOT_TRANSACTED";
		case SCARD_E_PCI_TOO_SMALL: return "SCARD_E_PCI_TOO_SMALL";
		case SCARD_E_PROTO_MISMATCH: return "SCARD_E_PROTO_MISMATCH";
		case SCARD_E_READER_UNAVAILABLE: return "SCARD_E_READER_UNAVAILABLE";
		case SCARD_E_READER_UNSUPPORTED: return "SCARD_E_READER_UNSUPPORTED";
#ifdef SCARD_E_SERVER_TOO_BUSY
		case SCARD_E_SERVER_TOO_BUSY: return "SCARD_E_SERVER_TOO_BUSY";
#endif
		case SCARD_E_SERVICE_STOPPED: return "SCARD_E_SERVICE_STOPPED";
		case SCARD_E_SHARING_VIOLATION: return "SCARD_E_SHARING_VIOLATION";
		case SCARD_E_SYSTEM_CANCELLED: return "SCARD_E_SYSTEM_CANCELLED";
		case SCARD_E_TIMEOUT: return "SCARD_E_TIMEOUT";
#ifdef SCARD_E_UNEXPECTED
		case SCARD_E_UNEXPECTED: return "SCARD_E_UNEXPECTED";
#endif
		case SCARD_E_UNKNOWN_CARD: return "SCARD_E_UNKNOWN_CARD";
		case SCARD_E_UNKNOWN_READER: return "SCARD_E_UNKNOWN_READER";
#ifdef SCARD_E_UNKNOWN_RES_MNG
		case SCARD_E_UNKNOWN_RES_MNG: return "SCARD_E_UNKNOWN_RES_MNG";
#endif
/* apparently E_UNEXPECTED and E_UNSUPPORTED are defined 
   by a buggy header file on Linux, causing a "double used constant"
   error. Just leave this out on Linux, then.
*/
#ifdef PHP_WIN32
                case SCARD_E_UNSUPPORTED_FEATURE: return "SCARD_E_UNSUPPORTED_FEATURE";
#endif
#ifdef SCARD_E_WRITE_TOO_MANY
		case SCARD_E_WRITE_TOO_MANY: return "SCARD_E_WRITE_TOO_MANY";
#endif
		case SCARD_F_COMM_ERROR: return "SCARD_E_WRITE_TOO_MANY";
		case SCARD_F_INTERNAL_ERROR: return "SCARD_F_INTERNAL_ERROR";
		case SCARD_F_UNKNOWN_ERROR: return "SCARD_F_UNKNOWN_ERROR";
		case SCARD_F_WAITED_TOO_LONG: return "SCARD_F_WAITED_TOO_LONG";
#ifdef SCARD_P_SHUTDOWN
		case SCARD_P_SHUTDOWN: return "SCARD_P_SHUTDOWN";
#endif
		case SCARD_S_SUCCESS: return "SCARD_S_SUCCESS";
#ifdef SCARD_W_CANCELLED_BY_USER
		case SCARD_W_CANCELLED_BY_USER: return "SCARD_W_CANCELLED_BY_USER";
#endif
#ifdef SCARD_W_CACHE_ITEM_NOT_FOUND
		case SCARD_W_CACHE_ITEM_NOT_FOUND: return "SCARD_W_CACHE_ITEM_NOT_FOUND";
#endif
#ifdef SCARD_W_CACHE_ITEM_STALE
		case SCARD_W_CACHE_ITEM_STALE: return "SCARD_W_CACHE_ITEM_STALE";
#endif
#ifdef SCARD_W_CACHE_ITEM_TOO_BIG
		case SCARD_W_CACHE_ITEM_TOO_BIG: return "SCARD_W_CACHE_ITEM_TOO_BIG";
#endif
#ifdef SCARD_W_CARD_NOT_AUTHENTICATED
		case SCARD_W_CARD_NOT_AUTHENTICATED: return "SCARD_W_CARD_NOT_AUTHENTICATED";
#endif
#ifdef SCARD_W_CHV_BLOCKED
		case SCARD_W_CHV_BLOCKED: return "SCARD_W_CHV_BLOCKED";
#endif
#ifdef SCARD_W_EOF
		case SCARD_W_EOF: return "SCARD_W_EOF";
#endif
		case SCARD_W_REMOVED_CARD: return "SCARD_W_REMOVED_CARD";
		case SCARD_W_RESET_CARD: return "SCARD_W_RESET_CARD";
#ifdef SCARD_W_SECURITY_VIOLATION
		case SCARD_W_SECURITY_VIOLATION: return "SCARD_W_SECURITY_VIOLATION";
#endif
		case SCARD_W_UNPOWERED_CARD: return "SCARD_W_UNPOWERED_CARD";
		case SCARD_W_UNRESPONSIVE_CARD: return "SCARD_W_UNRESPONSIVE_CARD";
		case SCARD_W_UNSUPPORTED_CARD: return "SCARD_W_UNSUPPORTED_CARD";
#ifdef SCARD_W_WRONG_CHV
		case SCARD_W_WRONG_CHV: return "SCARD_W_WRONG_CHV";
#endif
		default: return "Unknown";
	}
}

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

/* {{{ proto resource scard_establish_context()
   Return a a context to the PC/SC layer */
PHP_FUNCTION(scard_establish_context)
{
  SCARDCONTEXT scard_context = 0;
  LONG rc = 0;

  rc = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &scard_context);
  if (rc != SCARD_S_SUCCESS)
  {
	PCSC_G(last_errno)=rc;
    RETURN_FALSE;
  }
  
  ZEND_REGISTER_RESOURCE(return_value,(void*)scard_context,le_pcsc_ctx_res);
}
/* }}} */

/* {{{ proto boolean scard_is_valid_context(resource context)
   Checks if the PC/SC context is valid */
PHP_FUNCTION(scard_is_valid_context)
{
  LONG rc = 0;
  zval* ctx_res;
  SCARDCONTEXT context;
  
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &ctx_res) == FAILURE) {
    RETURN_NULL();
  }
  ZEND_FETCH_RESOURCE(context,SCARDCONTEXT,&ctx_res,-1,PHP_PCSC_CTX_RES_NAME,le_pcsc_ctx_res);
  
  rc = SCardIsValidContext(context);
  if (rc != SCARD_S_SUCCESS) {
	PCSC_G(last_errno)=rc;
    RETURN_FALSE;
  }
  RETURN_TRUE;
}
/* }}} */

/* {{{ proto boolean scard_release_context(long context)
   Invalidate the PC/SC context */
PHP_FUNCTION(scard_release_context)
{
  LONG rc = 0;
  zval* ctx_res;
  SCARDCONTEXT context;
  
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &ctx_res) == FAILURE) {
    RETURN_NULL();
  }
  ZEND_FETCH_RESOURCE(context,SCARDCONTEXT,&ctx_res,-1,PHP_PCSC_CTX_RES_NAME,le_pcsc_ctx_res);

  zend_hash_index_del(&EG(regular_list),Z_RESVAL_P(ctx_res));
  RETURN_TRUE;
}
/* }}} */

/* {{{ proto array scard_list_readers(resource context)
   Return an array of available PC/SC readers */
PHP_FUNCTION(scard_list_readers)
{
  char *strReaders = NULL;
  char *ptrReader;
  DWORD dwLen = SCARD_AUTOALLOCATE;
  LONG rc = 0;
  zval* ctx_res;
  SCARDCONTEXT context;
  
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &ctx_res) == FAILURE) {
    RETURN_NULL();
  }
  ZEND_FETCH_RESOURCE(context,SCARDCONTEXT,&ctx_res,-1,PHP_PCSC_CTX_RES_NAME,le_pcsc_ctx_res);
  
  rc = SCardListReaders(context, NULL, (char *) &strReaders, &dwLen);
  if (rc != SCARD_S_SUCCESS) {
	PCSC_G(last_errno)=rc;
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

/* {{{ proto resource scard_connect(resource context, string reader_name, [long preferred_protocol], [long &current_protocol])
   Return a handle to the card */
PHP_FUNCTION(scard_connect)
{
  DWORD dwPreferredProtocol = SCARD_PROTOCOL_T1|SCARD_PROTOCOL_T0; 
  DWORD dwCurrentProtocol;
  SCARDHANDLE hCard = 0;
  LONG rc = 0;
  zval* ctx_res;
  zval* current_protocol;
  SCARDCONTEXT context;
  char *strReaderName;
  int strReaderNameLen;
  
  MAKE_STD_ZVAL(current_protocol);
  ZVAL_LONG(current_protocol,0);
  
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs|lz", &ctx_res, &strReaderName, &strReaderNameLen, &dwPreferredProtocol,&current_protocol) == FAILURE) {
    RETURN_NULL();
  }
  ZEND_FETCH_RESOURCE(context,SCARDCONTEXT,&ctx_res,-1,PHP_PCSC_CTX_RES_NAME,le_pcsc_ctx_res);

  rc = SCardConnect(context, strReaderName, SCARD_SHARE_SHARED, dwPreferredProtocol, &hCard, &dwCurrentProtocol);
  if (rc != SCARD_S_SUCCESS) {
	PCSC_G(last_errno)=rc;
    RETURN_FALSE;
  }
  ZVAL_LONG(current_protocol,dwCurrentProtocol);
  
  ZEND_REGISTER_RESOURCE(return_value,(void*)hCard,le_pcsc_conn_res);
}
/* }}} */

/* {{{ proto boolean scard_disconnect(resource card_handle, [long disposition = SCARD_EJECT_CARD])
   Close a card connection obtained with scard_connect */
PHP_FUNCTION(scard_disconnect)
{
  DWORD dwDisposition = SCARD_EJECT_CARD;
  LONG rc;
  zval* conn_res;
  SCARDHANDLE hCard;
  
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r|l", &conn_res, &dwDisposition) == FAILURE) {
    return;
  }
  ZEND_FETCH_RESOURCE(hCard,SCARDHANDLE,&conn_res,-1,PHP_PCSC_CONN_RES_NAME,le_pcsc_conn_res);
  
  rc = SCardDisconnect(hCard, dwDisposition);
  if (rc != SCARD_S_SUCCESS) {
	PCSC_G(last_errno)=rc;
    RETURN_FALSE;
  }
  RETURN_TRUE;
}
/* }}} */

/* {{{ proto string scard_transmit(resource card_handle, string send_command)
   Transmit (and receive) data to (and from) the card */
PHP_FUNCTION(scard_transmit)
{
  SCARDHANDLE hCard;
  zval* conn_res;
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
  
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &conn_res, &apdu, &apduLen) == FAILURE) {
    return;
  }
  ZEND_FETCH_RESOURCE(hCard,SCARDHANDLE,&conn_res,-1,PHP_PCSC_CONN_RES_NAME,le_pcsc_conn_res);

  /* Are we in T=0 or T=1 ? Is the card powered? */
  rc = SCardStatus(hCard, NULL, NULL, &dwState, &dwProtocol, NULL, NULL);
  if (rc != SCARD_S_SUCCESS) {
	PCSC_G(last_errno)=rc;
    RETURN_FALSE;
  }
        
  if (!(dwState & SCARD_POWERED)) {
	PCSC_G(last_errno)=SCARD_W_UNPOWERED_CARD;
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
	PCSC_G(last_errno)=rc;
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

/* {{{ proto array scard_status([resource card_handle])
   Retrieve reader's or card's status */
PHP_FUNCTION(scard_status)
{
  zval* conn_res;
  SCARDHANDLE hCard = 0;
  char *strReader = NULL;
  DWORD dwProtocol, dwState;
  BYTE atrBuffer[32];
  DWORD atrLen;
  LONG rc;
  
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &conn_res) == FAILURE) {
    return;
  }
  ZEND_FETCH_RESOURCE(hCard,SCARDHANDLE,&conn_res,-1,PHP_PCSC_CONN_RES_NAME,le_pcsc_conn_res);
  
  atrLen = sizeof(atrBuffer);
  rc = SCardStatus(hCard, NULL, NULL, &dwState, &dwProtocol, atrBuffer, &atrLen);
  if (rc != SCARD_S_SUCCESS) {
	PCSC_G(last_errno)=rc;
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

/* {{{ proto long scard_last_errno()
   Retrieve last error code */
PHP_FUNCTION(scard_last_errno)
{
	RETURN_LONG(PCSC_G(last_errno));
}
/* }}} */

/* {{{ proto long scard_errstr(long errno)
   Retrieve string name of error code */
PHP_FUNCTION(scard_errstr)
{
  DWORD in_errno=0;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &in_errno) == FAILURE) {
    RETURN_NULL();
  }
  RETURN_STRING(php_pcsc_error_to_string(in_errno),1);
}
/* }}} */
