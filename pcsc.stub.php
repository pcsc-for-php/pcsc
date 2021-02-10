<?php

/**
 * @generate-function-entries
 * @generate-legacy-arginfo
 */

/**
 * @return resource|false
 */
function scard_establish_context() {}

/**
 * @param resource $context
 */
function scard_release_context($context): bool {}

/**
 * @param resource $context
 */
function scard_is_valid_context($context): bool {}

/**
 * @param resource $context
 */
function scard_list_readers($context): array|false {}

/**
 * @param resource $context
 * @return resource|false
 */
function scard_connect($context, string $reader_name, int $preferred_protocol=SCARD_PROTOCOL_T0|SCARD_PROTOCOL_T1, int &$current_protocol=NULL): array|false {}

/**
 * @param resource $card
 * @return resource|false
 */
function scard_disconnect($card, int $disposition=SCARD_EJECT_CARD): bool {}

/**
 * @param resource $card
 * @return resource|false
 */
function scard_transmit($card, string $command): string|false {}

/**
 * @param resource $card
 * @return resource|false
 */
function scard_status($card): array|false {}

function scard_last_errno(): int {}

function scard_errstr(int $errno): string {}

