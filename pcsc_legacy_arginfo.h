/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 3e1df1d509b6416c1eb997f61295c26d9ad0fd03 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_scard_establish_context, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_scard_release_context, 0, 0, 1)
	ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()

#define arginfo_scard_is_valid_context arginfo_scard_release_context

#define arginfo_scard_list_readers arginfo_scard_release_context

ZEND_BEGIN_ARG_INFO_EX(arginfo_scard_connect, 0, 0, 2)
	ZEND_ARG_INFO(0, context)
	ZEND_ARG_INFO(0, reader_name)
	ZEND_ARG_INFO(0, preferred_protocol)
	ZEND_ARG_INFO(1, current_protocol)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_scard_disconnect, 0, 0, 1)
	ZEND_ARG_INFO(0, card)
	ZEND_ARG_INFO(0, disposition)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_scard_transmit, 0, 0, 2)
	ZEND_ARG_INFO(0, card)
	ZEND_ARG_INFO(0, command)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_scard_status, 0, 0, 1)
	ZEND_ARG_INFO(0, card)
ZEND_END_ARG_INFO()

#define arginfo_scard_last_errno arginfo_scard_establish_context

ZEND_BEGIN_ARG_INFO_EX(arginfo_scard_errstr, 0, 0, 1)
	ZEND_ARG_INFO(0, errno)
ZEND_END_ARG_INFO()


ZEND_FUNCTION(scard_establish_context);
ZEND_FUNCTION(scard_release_context);
ZEND_FUNCTION(scard_is_valid_context);
ZEND_FUNCTION(scard_list_readers);
ZEND_FUNCTION(scard_connect);
ZEND_FUNCTION(scard_disconnect);
ZEND_FUNCTION(scard_transmit);
ZEND_FUNCTION(scard_status);
ZEND_FUNCTION(scard_last_errno);
ZEND_FUNCTION(scard_errstr);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(scard_establish_context, arginfo_scard_establish_context)
	ZEND_FE(scard_release_context, arginfo_scard_release_context)
	ZEND_FE(scard_is_valid_context, arginfo_scard_is_valid_context)
	ZEND_FE(scard_list_readers, arginfo_scard_list_readers)
	ZEND_FE(scard_connect, arginfo_scard_connect)
	ZEND_FE(scard_disconnect, arginfo_scard_disconnect)
	ZEND_FE(scard_transmit, arginfo_scard_transmit)
	ZEND_FE(scard_status, arginfo_scard_status)
	ZEND_FE(scard_last_errno, arginfo_scard_last_errno)
	ZEND_FE(scard_errstr, arginfo_scard_errstr)
	ZEND_FE_END
};
