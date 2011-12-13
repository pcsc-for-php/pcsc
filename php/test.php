<?php

/* Just a test script for checking the implementation... */

if (!extension_loaded('pcsc')) {
  dl('pcsc.so');
}

include("./pcsc.class.php");

$foo = new PCSC();

echo "Create Context:\n";
var_dump($foo->context);

echo "List Readers:\n";
var_dump($foo->listreaders());

echo "Connect Card:\n";
var_dump($foo->connect("OMNIKEY CardMan 5x21 00 01"));

#echo "Reconnect:\n";
#var_dump($foo->reconnect());

echo "Some Transmits:\n";
var_dump($foo->transmit("00a4040c0cD2760001354B414E4D30310000"));
var_dump($foo->transmit("0084000008"));
var_dump($foo->transmit("0084000008"));
var_dump($foo->transmit("0084000008"));

echo "Is Valid Context?\n";
var_dump($foo->isvalidcontext());

echo "Status:\n";
var_dump($foo->status());

echo "Disconnect Card:\n";
var_dump($foo->disconnect());

echo "Release Context:\n";
var_dump($foo->releasecontext());

?>
