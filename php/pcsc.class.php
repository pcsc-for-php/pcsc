<?php
/*
 * Don't use this! this is a raw and dirty written class just for testing some
 * stuff... Johannes
 */

class PCSC {

  public $context;
  public $card;
  public $readers;
  public $connection;

  function __construct() {
    $this->context = scard_establish_context();
  }
  
  function __destruct() {
    $this->context = scard_release_context($this->context);
  }

  function connect($reader) {
    return $this->connection = scard_connect($this->context, $reader);
  }
  
  /*function reconnect() {
    return $this->connection = scard_reconnect($this->connection);
  }*/
  
  function disconnect() {
    return scard_disconnect($this->connection);
  }
  
  function listreaders() {
    return $this->readers = scard_list_readers($this->context);
  }
  
  function transmit($apdu) {
    return scard_transmit($this->connection, $apdu);
  }
  
  function isvalidcontext() {
 		return scard_is_valid_context($this->context);
  }
  
  function releasecontext() {
 		return scard_release_context($this->context);
  }
  
  function status() {
  	return scard_status($this->connection);
  }
}

?>
