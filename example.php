<?php

header('Content-Type: text/html; charset=UTF-8'); //Make it clear that we're going to output UTF-8

$hb = "hb.exe ";
$url = escapeshellarg("http://www.google.com"); //You probably want to get the URL from GET/POST or whatever other method you want.

exec("$hb \"$url\"", $result);
foreach($result as $line) echo $line;

?>