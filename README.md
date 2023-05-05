# SecureTap-RFID

A security system that uses RFID to grant or deny access.

#Python -- dbConnect_Auth.py

---

- In the Python code
  under the config object replace the user, password, host and port properties with the actual values

- In the query string variable, replace 'table_name' the actual table_name
- Check the USB port at which your Arduino is connected, then replace USBPORT with that value
- Make sure that the port next to the USB port name is correct

#Arduino Code

---

- Upload your code to your Arduino
- Make sure that the code is correctly uploaded
- Make sure that the Serial Monitor in Arduino is not opened (Arduino IDE's serial-monitor is single-slave, hence cannot serve both the IDE and Python script that is using Serial communication to communication with the Arduino)
