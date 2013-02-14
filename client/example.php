<?php

header('Content-Type: text/html; charset=UTF-8'); //Make it clear that we're going to output UTF-8

$headless_browser = "client.exe ";
$url = escapeshellarg("http://www.google.com"); //You probably want to get the URL from GET/POST or whatever other method you want.

function runExternal($cmd, &$code){
  $descriptorspec = array(
    0 => array("pipe", "r"), // stdin is a pipe that the child will read from
    1 => array("pipe", "w"), // stdout is a pipe that the child will write to
    2 => array("pipe", "w") // stderr is a file to write to
  );
  $pipes= array();
  $process = proc_open($cmd, $descriptorspec, $pipes);

  $output= "";

  if(!is_resource($process)) return false;

  fclose($pipes[0]);

  stream_set_blocking($pipes[1],false);
  stream_set_blocking($pipes[2],false);

  while(true){
    $read = array(); 
    $write = NULL;
    $ex = NULL;
    if(!feof($pipes[1])) $read[] = $pipes[1];
    if(!feof($pipes[2])) $read[] = $pipes[2];
    
    if(empty($read)) break;

    $ready = stream_select($read, $write, $ex, 2);

    if($ready === false){
      break; #should never happen; something died
    }else{
      foreach($read as $r){
        $output .= stream_get_contents($r);
      }
    }
  }

  fclose($pipes[1]);
  fclose($pipes[2]);

  $code= proc_close($process);

  return $output;
}
$result = runExternal("$headless_browser $url", $code);
echo $result;

?>