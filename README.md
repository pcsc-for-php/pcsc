# PC/SC for PHP

## About

This is the only extension for using [PC/SC](http://www.pcscworkgroup.com/) based smart cards with [PHP](http://www.php.net). It is a wrapper to the wonderful and free project by Ludovic Rousseau, [PCSC-Lite](https://pcsclite.apdu.fr/), which is the middleware to access a smart card using SCard API (PC/SC). Since PCSC-Lite is compatible to the winscard API it should be possible to compile this extension using a Windows or macOS operating system.

Thanks are going to Johann Dantant! He provided a PC/SC extension for PHP since 2005 and I reused some of his code. He allowed me to relicense these parts under the terms of the PHP license so I could integrate PCSC-Lite native into PHP.

## Installation

I recommend to install the PECL extension the "PHP" way:

```
pecl install pcsc-beta
```

You can install the latest code by downloading the sources and compile yourself too.

```
git clone https://github.com/pcsc-for-php/pcsc.git
cd pcsc
phpize
./configure
make
make install
```

After that you have all needed files in ./modules/ .

## API

The extension currently provides the following API (alphabetical order):

### pcsc_stringify_error($errno);

Returns $errstr for $errno or NULL.

**NOT IMPLEMENTED!** - Should be available!

Duplicate of scard_errstr() but this should be the default.

### scard_begin_transaction($connection);

**NOT IMPLEMENTED!** - Should be available!

Establishes a temporary exclusive access mode for doing a serie of commands in a transaction.

You might want to use this when you are selecting a few files and then writing a large file so you can make sure that another application will not change the current file. If another application has a lock on this reader or this application is in SCARD_SHARE_EXCLUSIVE there will be no action taken.

### scard_cancel($context);

**NOT IMPLEMENTED!** - Maybe not useful because of this extension is for server side usage designed but since we want the API implemented it should be available.

### scard_connect($context, "OMNIKEY CardMan 5x21 00 00" [, int $protocol]);

Connects to a card. Returns the $connection to a reader or FALSE.

Where optional $protocol is:

 * 1 = T=0
 * 2 = T=1

Default $protocol is T=1.

### scard_control($connection);

**NOT IMPLEMENTED!** - Should be available!

Sends a command directly to the IFD Handler (reader driver) to be processed by the reader.

### scard_disconnect($connection);

Disconnects the $connection to a card. Returns the TRUE if disconnecting was succesful or FALSE.

### scard_end_transaction($connection);

**NOT IMPLEMENTED!** - Should be available!

Ends a previously begun transaction.

The calling application must be the owner of the previously begun transaction or an error will occur.

### scard_errstr($errno); - Not PC/SC standard.

Returns $errstr for $errno or NULL.

### scard_establish_context();

Returns the application $context to the PC/SC resource manager.

### scard_get_attrib($connection);

**NOT IMPLEMENTED!** - Should be available!

Get an attribute from the IFD Handler (reader driver).

### scard_get_status_change($context);

**NOT IMPLEMENTED!** - Should be available!

Blocks execution until the current availability of the cards in a specific set of readers changes.

### scard_is_valid_context($context);

Returns TRUE if $context is valid or FALSE if $context is not valid.

### scard_last_errno(); - Not PC/SC standard.

Returns the last $errno or nothing? NULL or FALSE? (TODO)

### scard_list_reader_groups($context);

**NOT IMPLEMENTED!** - Should be available!

Returns a list of currently available reader groups on the system.

### scard_list_readers($context);

Returns an array of available readers or FALSE.

#### Example:

```
array(3) {
  [0]=>
  string(26) "OMNIKEY CardMan 5x21 00 00"
  [1]=>
  string(26) "OMNIKEY CardMan 5x21 00 01"
  [2]=>
  string(76) "SCL01x Contactless Reader [SCL01x Contactless Reader] (21161009200722) 00 00"
}
```

### scard_reconnect($connection);

**NOT IMPLEMENTED!** - Should be available!

Returns the $connection to a reader or FALSE.

### scard_release_context($context);

Releases the application $context.

### scard_set_attrib($connection);

**NOT IMPLEMENTED!** - Should be available!

Set an attribute of the IFD Handler.

### scard_status($connection);

Returns the status array or FALSE.

#### Example:

```
array(7) {
  ["state"]=>
  int(52)
  ["SCARD_PRESENT"]=>
  int(1)
  ["SCARD_POWERED"]=>
  int(1)
  ["SCARD_NEGOTIABLE"]=>
  int(1)
  ["SCARD_PROTOCOL_T1"]=>
  int(1)
  ["PROTOCOL"]=>
  string(3) "T=1"
  ["ATR"]=>
  string(28) "3B8980014A434F5033315632324A"
}
```

### scard_transmit($connection, $apdu);

Returns the response $apdu as string or FALSE.

## License

This code is licensed under the terms of the PHP License version 3.01. PCSC-Lite is licensed in a way where it is possible to integrate it native in the PHP environment.

## Links

 * [PECL Project Page](http://pecl.php.net/package/pcsc) - Page for package download at PHP.net
 * [PC/SC Worgroup](http://www.pcscworkgroup.com/) - Homepage and definition file downloads
 * [PC/SC](http://en.wikipedia.org/wiki/PC/SC) - PC/SC at Wikipedia
 * [PC/SC-Lite](https://pcsclite.apdu.fr/) - The free and open implementation of the PC/SC SCard API for UNIX
 * [PCSC sample in PHP5](http://ludovicrousseau.blogspot.de/2015/01/pcsc-sample-in-php5.html) - Ludovic Rousseau about "PC/SC for PHP"
 * [winscard.h header](https://docs.microsoft.com/en-us/windows/win32/api/winscard/) - Microsoft Docs
 * [PC/SC API from PCSC-Lite](https://pcsclite.apdu.fr/api/group__API.html)

