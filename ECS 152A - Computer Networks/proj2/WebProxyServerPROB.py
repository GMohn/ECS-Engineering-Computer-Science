# Import socket module
from socket import *    

# Create a TCP server socket
#(AF_INET is used for IPv4 protocols)
#(SOCK_STREAM is used for TCP)

serverSocket = socket(AF_INET, SOCK_STREAM)

# Fill in start
serverSocket.bind(('', 8888))
serverSocket.listen(1)
print('Create socket')
# Fill in end 

#Initialize cache
cache = {}



# Server should be up and running and listening to the incoming connections
while True:
	print('Ready to serve...')
	fileInCache = False
	# Set up a new connection from the client
	connectionSocket, addr = serverSocket.accept()
	print('Connection from: ', addr)
	# If an exception occurs during the execution of try clause
	# the rest of the clause is skipped
	# If the exception type matches the word after except
	# the except clause is executed
	try:
		# Receives the request message from the client
		message =  connectionSocket.recv(1024).decode()
		print('message: ',message)
		# getting index errors if empty message or is favicon
		if ((message.split()[1] == None) or (message.split()[1] == '/favicon.ico')):
			continue
		# Extract the path of the requested object from the message
		# The path is the second part of HTTP header, identified by [1]
		url = message.split()[1]
		host = url.split('/')[1].split(':')[0]
		port = url.split('/')[1].split(':')[1]
		filename = url.split("/")[-1]

		# Because the extracted path of the HTTP request includes 
		# a character '\', we read the path from the second character 
		print('opening file....', url[1:])
		f = open(url[1:], "rb")

		# Store the entire contenet of the requested file in a temporary buffer
		print("reading output data")
		outputdata = f.read()#Fill in start         #Fill in end
		fileInCache = True
		# Send the HTTP response header line to the connection socket
		# Fill in start
		responseMessage = 'HTTP/1.1 200 OK\r\n'
		responseHeaders = 'Content-Type: image/jpeg\r\nContent-Length: {}\r\n\r\n'.format(len(outputdata))
		connectionSocket.send(responseMessage.encode())
		connectionSocket.send(responseHeaders.encode())
        # Fill in end
 
		# Send the content of the requested file to the connection socket
		# for i in range(0, len(outputdata)):  
		# 	connectionSocket.send(outputdata[i].encode())
		# connectionSocket.send("\r\n".encode())
		print('sending outputdata')
		for i in range(0, len(outputdata), 1024):
			connectionSocket.send(outputdata[i:i+1024])
		connectionSocket.send('\r\n'.encode())

		# Close the client connection socket
		connectionSocket.close()
		f.close()

	except IOError:
		# Send HTTP response message for file not found
		# Fill in start
		if filename in cache:
			print('file in cache')
			for i in range(0, len(cache[filename]), 1024):
				connectionSocket.send(cache[filename][i:i+1024])
			connectionSocket.send('\r\n'.encode())
		else :
			try:
				print('file NOT in cache')
				
				print('hostName: ',filename)
				try:
					proxySocket = socket(AF_INET, SOCK_STREAM)
					print('trying to connect to proxySocket')
					proxySocket.connect((host,int(port)))
					request = b'GET /' + filename.encode() + b' HTTP/1.1\r\nHost: ' + host.encode() + b'\r\n\r\n'
					print(request)
					proxySocket.sendall(request)
					print('proxySocket sent message')
					data = b''
					while True:
						print('receiving data')
						chunk = proxySocket.recv(1024)
						if not chunk:
							break
						data = data + chunk
					outputdata = data
					cache[filename] = outputdata
					print('sending outputdata')
					for i in range(0, len(outputdata), 1024):
						connectionSocket.send(outputdata[i:i+1024])
					connectionSocket.send('\r\n'.encode())
				except Exception as e:
					print(e)
					print('cant put file in proxy cache')
					connectionSocket.send("HTTP/1.1 400 Bad Request\r\n\r\n".encode())
					proxySocket.close()

			except:
				connectionSocket.send("HTTP/1.1 404 Not found\r\n\r\n".encode())
        # Fill in end
        
		# Close the client connection socket
		# Fill in start
		connectionSocket.close()
		proxySocket.close()
        # Fill in end

serverSocket.close()  

