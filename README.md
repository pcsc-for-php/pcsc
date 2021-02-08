<h2 id="Notes">Notes</h2>

<p>This code does not work with version 7 of PHP! Currently I am not able to fix this. If you want to take over development or submit patches it is very welcome... Please <a href="contact.html">contact</a> me if you are interested.</p>

<p>I do not write PHP code since many years so it would be great to find a maintainer for this code.</p>

<h2 id="About">About</h2>

<p>This is the only extension for using <a href="http://www.pcscworkgroup.com/" class="ext">PC/SC</a> based smart cards with <a href="http://www.php.net" class="ext">PHP</a>5. It is a wrapper to the wonderful and free project by Ludovic Rousseau, <a href="http://pcsclite.alioth.debian.org/" class="ext">PCSC-Lite</a>, which is the middleware to access a smart card using SCard API (PC/SC). Since PCSC-Lite is compatible to the winscard API it should be possible to compile this extension using a Windows(R) operating system. Currently I only take focus on Linux environments.</p>

<p>Thanks are going to Johann Dantant! He provides a PC/SC extension for PHP since 2005 and I reused some of his code. He allowed me to relicense these parts under the terms of the PHP license so I could integrate PCSC-Lite natively into PHP.</p>

<h2 id="Installation">Installation</h2>

<p>I recommend to install the PECL extension the "PHP" way:</p>

<pre>pecl install pcsc-alpha</pre>

<p>You can install the latest version by downloading the sources and compile yourself too... :)</p>

<pre>wget http://pecl.php.net/get/pcsc-0.3.1.tgz
tar -xvf pcsc-0.3.1.tgz
cd pcsc-0.3.1
phpize
./configure
make
make install</pre>

<p>After that you have all needed files in ./modules/</p>

<h2 id="API">API</h2>

<p>The extension currently provides the following API:</p>

<h3 id="scard_establish_context">scard_establish_context();</h3>

<p>Returns the application $context to the PC/SC resource manager.</p>

<h3 id="scard_is_valid_context">scard_is_valid_context($context);</h3>

<p>Returns TRUE if $context is valid or FALSE if $context is not valid.</p>

<h3 id="scard_release_context">scard_release_context($context);</h3>

<p>Releases the application $context.</p>

<h3 id="scard_list_readers">scard_list_readers($context);</h3>

<p>Returns an array of available readers or FALSE.</p>

<h5>Example:</h5>

<pre>array(3) {
  [0]=&gt;
  string(26) "OMNIKEY CardMan 5x21 00 00"
  [1]=&gt;
  string(26) "OMNIKEY CardMan 5x21 00 01"
  [2]=&gt;
  string(76) "SCL01x Contactless Reader [SCL01x Contactless Reader] (21161009200722) 00 00"
}
</pre>

<h3 id="scard_connect">scard_connect($context, "OMNIKEY CardMan 5x21 00 00");</h3>

<p>Connects to a card. Returns the $connection to a reader or FALSE.</p>

<h3 id="scard_reconnect">scard_reconnect($connection);</h3>

<p>Returns the $connection to a reader or FALSE.</p>

<h3 id="scard_disconnect">scard_disconnect($connection);</h3>

<p>Disconnects the $connection to a card. Returns the TRUE if disconnecting was succesful or FALSE.</p>

<h3 id="scard_transmit">scard_transmit($connection, $apdu);</h3>

<p>Returns the response $apdu as string or FALSE.</p>

<h3 id="scard_status">scard_status($connection);</h3>

<p>Returns the status or FALSE.</p>

<h3 id="scard_cancel">scard_cancel($context);</h3>

<h2 id="Code">Code</h2>

<p>The code has successful been released to the official code repository <a href="http://pecl.php.net" class="ext">pecl.php.net</a>... ;)

<ul>
  <li><a href="http://pecl.php.net/package/pcsc" class="ext">PECL Project Page</a></li>
  <li><a href="http://svn.php.net/viewvc/pecl/pcsc/trunk/" class="ext">PHP SVN Code Browser</a></li>
</ul>

<p>You could get the code using the following command:</p>

<pre>svn checkout http://svn.php.net/repository/pecl/pcsc/trunk pcsc</pre>

<!--<h2>Latest commits:</h2>

<div id="github-commits"></div>
<script>
$(function() {
      $('#github-commits').githubInfoWidget({ user: 'hanez', repo: 'pcsc-for-php', branch: 'master', last: 30 });
});
</script>-->

<h2 id="License">License</h2>

<p>This code is licensed under the terms of the PHP License version 3.01. PCSC-Lite is licensed in a way where it is possible to integrate it native in the PHP environment.</p>

<h2 id="Links">Links</h2>

<ul>
	<li><a href="http://www.pcscworkgroup.com/" class="ext">PC/SC Worgroup</a> - Homepage and definition file downloads.</li>
	<li><a href="http://en.wikipedia.org/wiki/PC/SC" class="ext">PC/SC</a> - PC/SC at Wikipedia.</li>
	<li><a href="http://pcsclite.alioth.debian.org/" class="ext">PC/SC-Lite</a> - The free and open implementation of the PC/SC SCard API for UNIX</li>
	<li><a href="http://ludovicrousseau.blogspot.de/2015/01/pcsc-sample-in-php5.html" class="ext">PCSC sample in PHP5</a> - Ludovic Rousseau about "PC/SC for PHP"</li>
</ul>
