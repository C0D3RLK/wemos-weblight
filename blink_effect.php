<?php
/*
* WEB LIGHT: Effect1-BLINK
* https://github.com/C0D3RLK/wemos-weblight/
* 86kanth@gmail.com | Open
*
*/


$toggle = 0;
$nodeIP = "10.10.10.1"; //Change this IP to yours

for ($i = 0; $i >= $toggle; $i++){
if ($toggle == 0){exec("curl -m 1 http://".$nodeIP."/LED_STEADY=ON"); $toggle=1;} //Change the function as you desired
sleep(2);
if ($toggle == 1){exec("curl -m 1 http://".$nodeIP."/LED_STEADY=OFF");$toggle=0;} //Change the function as you desired
}
?>
