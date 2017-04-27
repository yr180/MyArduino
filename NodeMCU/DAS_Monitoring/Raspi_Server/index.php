<?php

	include("connectDB.php");

	$link=Connection();

	$result=mysql_query("SELECT * FROM templog ORDER BY timestamp DESC",$link);
?>

<html>
   <head>
      <title>IOT with ESP</title>
      <link rel="stylesheet" href="style.css">
   </head>
<body>
    <div class="title"><h1>Temperature sensor readings</h1></div>

    <div class="about">
        <div class="screenshot"><img src="http://docs.thinger.io/arduino/assets/nodemcu.png" alt="NodeMCU"
        title="NodeMCU" img height=240px img width=380px></div>
        <div class="description">
        NodeMCU is an open source IoT platform.It includes firmware which runs on the ESP8266 Wi-Fi SoC from Espressif Systems, and hardware which is based on the ESP-12 module.Some creative ESP8266 enthusiasts have developed an Arduino core for the ESP8266 WiFi SoC that is available at the <a rel="nofollow" target="_blank"
        href="https://github.com/esp8266/Arduino">GitHub ESP8266 Core webpage</a>
        </div>
    </div>

    <div class = "data">
    	<h5 style="padding:0px; color:#7C8B88;"> Data From ESP1: </h5>
       	<table style="font-size:20; text-align:center;" border="1" cellspacing="1" cellpadding="1">
		  <tr class = "title">
		  	   <td>&nbsp;Timestamp&nbsp;</td>
			   <td>&nbsp;Temperature&nbsp;</td>
		  </tr>

        	<?php
		  if($result!==FALSE){
		     while($row = mysql_fetch_array($result)) {
		        printf("<tr><td> &nbsp;%s </td><td> &nbsp;%s&nbsp; </td></tr>",
		           $row["timestamp"], $row["temperature"]);
		     }
		     mysql_free_result($result);
		     mysql_close();
		  }
        	?>

       	</table>
    </div>

</body>
</html>


