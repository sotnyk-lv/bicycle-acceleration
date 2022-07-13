import serial

serialPort = serial.Serial(port = "COM7", baudrate=115200,
                           bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)

serialString = ''

with open('../resources/acc_mag_res.list', 'a') as file:
    try:
        while True:
            if(serialPort.in_waiting > 0):
                # Read data out of the buffer until a carraige return / new line is found
                serialString = serialPort.readline()

                # Print the contents of the serial data
                # print(serialString.decode('Ascii'))

                data = serialString.decode('Ascii')

                if data[:3] != 'acc':
                    continue
                file.write(data[:-1])
    except KeyboardInterrupt:
        serialPort.close()
