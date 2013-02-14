<?php

header('Content-Type: text/html; charset=UTF-8'); //Make it clear that we're going to output UTF-8

$headless_browser = "client.exe ";
$url = escapeshellarg("http://www.google.com"); //You probably want to get the URL from GET/POST or whatever other method you want.

echo shell_exec("$headless_browser $url");

?>