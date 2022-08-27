#include <ESP8266WiFi.h>
    #include <WiFiClient.h>
    #include <ESP8266WebServer.h>
    /* Set these to your desired credentials. */
    const char *ssid = "ICO"; //Enter your WIFI ssid
    const char *password = "9876543210"; //Enter your WIFI password
    ESP8266WebServer server(80);
    void handleRoot() {
     server.send(200, "text/html", " <html> <style> button:active { background-color: yellow; } .flexMeRow { display: flex; flex-direction: row; justify-content: center; } .flexMeCol { display: flex; flex-direction: column; justify-content: center; } .flexMeCenter { display: flex; min-height: 100vh; flex-direction: column; justify-content: center; align-items: center; } </style> <body> <div class=\"flexMeCenter\"> <div class=\"flexMeCol\"> <div class=\"flexMeRow\"> <button type=\"submit\" form=\"forward\" id=\"control4\">FORWARD</button> </div> <div class=\"flexMeRow\"> <form action=\"/left\" method=\"get\" id=\"left\"></form> <form action=\"/right\" method=\"get\" id=\"right\"></form> <form action=\"/forward\" method=\"get\" id=\"forward\"></form> <form action=\"/back\" method=\"get\" id=\"back\"></form> <form action=\"/stop\" method=\"get\" id=\"stop\"></form> <button form=\"left\" type=\"submit\" id=\"control2\">LEFT</button> <button form=\"stop\" type=\"submit\" id=\"stop\">STOP</button> <button form=\"right\" type=\"submit\" id=\"control1\">RIGHT</button> </div> <div class=\"flexMeRow\"> <button form=\"back\" type=\"submit\" id=\"control3\">BACK</button> </div> </div> <br /> <br /> <div class=\"flexMeRow\"> <label for=\"vol\">Throttle (between 0 and 100):</label> <input type=\"range\" id=\"points\" onchange=\"myfunction()\" name=\"Speed controller\" min=\"0\" max=\"100\" value=\"100\" form = \"speed\" /> <div  value=\"getvalue()\"></div> <form action=\"/speed\" method=\"get\" id=\"speed\"> <!-- <div id=\"sendSpeed\" value=\"inputVal()\"></div> --> </form> <div id=\"throttleValue\" ></div> <button type=\"submit\" form=\"speed\" id=\"speedButt\" style=\"display:none\"></button> </div> </div> </body> <script> function myfunction() { var value = document.getElementById('throttleValue'); var input = document.getElementById('points'); var speedButt=document.getElementById(\"speedButt\"); var speed=document.getElementById(\"speed\"); speed.action=\"/speed?par1=hi\";    speedButt.click() ;console.log(input.value); value.innerHTML = input.value speedButt.click(); } function inputVal(){ var input = document.getElementById('points'); console.log(input.value + \"right\"); return(input.value) } function getvalue() { var x = document.getElementById('throttleValue').innerHTML; return x; } myfunction(); </script> </html>");
    }
    void handleSave() {
     if (server.arg("pass") != "") {
       Serial.println(server.arg("pass"));
     }
    }

void handleGenericArgs() { //Handler

String message = "Number of args received:";
message += server.args();            //Get number of parameters
message += "\n";                            //Add a new line

for (int i = 0; i < server.args(); i++) {

message += "Arg nº" + (String)i + " –> ";   //Include the current iteration value
message += server.argName(i) + ": ";     //Get the name of the parameter
message += server.arg(i) + "\n";              //Get the value of the parameter

} 
Serial.println(message);

handleRoot();       //Response to the HTTP request

}

    void Forward()
{
digitalWrite(D5,HIGH);
digitalWrite(D8,LOW);
digitalWrite(D7,HIGH);
digitalWrite(D6,LOW);


}

 void Back()
{
digitalWrite(D8,HIGH);
digitalWrite(D5,LOW);
digitalWrite(D6,HIGH);
digitalWrite(D7,LOW);


}

void Right()
{
digitalWrite(D5,HIGH);
digitalWrite(D5,LOW);
digitalWrite(D6,LOW);
digitalWrite(D7,LOW);

}

void Left()
{
digitalWrite(D5,LOW);
digitalWrite(D8,LOW);
digitalWrite(D6,HIGH);
digitalWrite(D7,LOW);

}


void Stop()
{
digitalWrite(D5,LOW);
digitalWrite(D8,LOW);
digitalWrite(D6,LOW);
digitalWrite(D7,LOW);

}




    void setup() {
     pinMode(D6, OUTPUT);
     pinMode(D7, OUTPUT);
      pinMode(D5, OUTPUT);
     pinMode(D8, OUTPUT);
    
     delay(3000);
     Serial.begin(74880);
     Serial.println();
     Serial.print("Configuring access point...");
     WiFi.begin(ssid, password);
     while (WiFi.status() != WL_CONNECTED) {
       delay(500);
       Serial.print(".");
     }
     Serial.println("");
     Serial.println("WiFi connected");
     Serial.println("IP address: ");
     Serial.println(WiFi.localIP());
     server.on ( "/", handleRoot );
     server.on ("/save", handleSave);
     server.begin();
     Serial.println ( "HTTP server started" );
     server.on("/forward", []() {
      Forward();
       Serial.println("forward");
       handleRoot();
     });
     server.on("/back", []() {
     Back();
       Serial.println("back");
       handleRoot();
     });

//     server.on("/left", []() {
//     Left();
//       Serial.println("left");
//       handleRoot();
//     });

    server.on("/speed",handleGenericArgs);
      
       server.on("/right", []() {
     Right();
       Serial.println("right");
       handleRoot();
     });

     server.on("/stop", []() {
     Stop();
       Serial.println("stop");
       handleRoot();
     });
    }
    void loop() {
     server.handleClient();
    } 
