import mysql.connector
import serial
#  import time

cardUid = ""
valid = False
size = 0

# set up the connection details
config = {
    'user': 'xxxxxxx',
    'password': 'xxxxxxxxx',
    'host': 'xxxxxxxxx',
    'database': 'xxxxxxxxx'
}

# connect to the database
cnx = mysql.connector.connect(**config)

# perform some queries, for example:
cursor = cnx.cursor()
query = "SELECT * FROM table_name"
cursor.execute(query)
results = cursor.fetchall()

# close the connection
cnx.close()

# Define the serial port and baud rate
ser = serial.Serial('USBPORT', 9600)

while True:
    # Read data from the serial port
    valid = False
    cardUid = ser.readline().decode().rstrip()
    print(cardUid)
    # Print the dat
    for result in results:
        (_, uid) = result
        if (cardUid == uid):
            valid = True
            break
        else:
            continue
    size = len(cardUid)
    if (size == 8):
        if (valid):
            print('valid')
            ser.write('t'.encode())
        else:
            print('invalid')
            ser.write('f'.encode())