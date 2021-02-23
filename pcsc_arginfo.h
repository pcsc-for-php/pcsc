/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 676b86ff0a1ee4d762d86126e8068f4cb6805272 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_scard_establish_context, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_scard_release_context, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()

#define arginfo_scard_is_valid_context arginfo_scard_release_context

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_scard_list_readers, 0, 1, MAY_BE_ARRAY|MAY_BE_FALSE)
	ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_scard_connect, 0, 2, MAY_BE_ARRAY|MAY_BE_FALSE)
	ZEND_ARG_INFO(0, context)
	ZEND_ARG_TYPE_INFO(0, reader_name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, preferred_protocol, IS_LONG, 0, "SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(1, current_protocol, IS_LONG, 0, "NULL")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_scard_disconnect, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, card)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, disposition, IS_LONG, 0, "SCARD_EJECT_CARD")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_scard_begin_transaction, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, card)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_scard_end_transaction, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, card)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, disposition, IS_LONG, 0, "SCARD_LEAVE_CARD")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_scard_transmit, 0, 2, MAY_BE_STRING|MAY_BE_FALSE)
	ZEND_ARG_INFO(0, card)
	ZEND_ARG_TYPE_INFO(0, command, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_scard_status, 0, 1, MAY_BE_ARRAY|MAY_BE_FALSE)
	ZEND_ARG_INFO(0, card)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_scard_last_errno, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_scard_errstr, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, errno, IS_LONG, 0)
ZEND_END_ARG_INFO()


ZEND_FUNCTION(scard_establish_context);
ZEND_FUNCTION(scard_release_context);
ZEND_FUNCTION(scard_is_valid_context);
ZEND_FUNCTION(scard_list_readers);
ZEND_FUNCTION(scard_connect);
ZEND_FUNCTION(scard_disconnect);
ZEND_FUNCTION(scard_begin_transaction);
ZEND_FUNCTION(scard_end_transaction);
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
	ZEND_FE(scard_begin_transaction, arginfo_scard_begin_transaction)
	ZEND_FE(scard_end_transaction, arginfo_scard_end_transaction)
	ZEND_FE(scard_transmit, arginfo_scard_transmit)
	ZEND_FE(scard_status, arginfo_scard_status)
	ZEND_FE(scard_last_errno, arginfo_scard_last_errno)
	ZEND_FE(scard_errstr, arginfo_scard_errstr)
	ZEND_FE_END
};
