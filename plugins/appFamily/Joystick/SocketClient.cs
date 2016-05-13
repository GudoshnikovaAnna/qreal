using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Networking;
using Windows.Networking.Sockets;
using Windows.Storage.Streams;

namespace GamepadClientNamespace
{
    class GamepadClient
    {
        static private StreamSocket clientSocket;
        static private HostName serverHost;
        static private string serverHostnameString = "192.168.77.1";
        static private string serverPort = "4444";
        static private bool connected = false;
        static private DataWriter writer;

        static public void Connect(string address, string port)
        {
            if (!connected)
            {
                clientSocket = new StreamSocket();

                try
                {
                    serverHost = new HostName(address);
                    serverPort = port;
                    serverHostnameString = address;
                    writer = new DataWriter(clientSocket.OutputStream);

                    clientSocket.ConnectAsync(serverHost, serverPort);
                    connected = true;
                }
                catch (Exception)
                {
                    clientSocket.Dispose();
                    clientSocket = null;

                    throw new ConnectionErrorException();
                }
            }
            else
            {
                clientSocket.Dispose();
                clientSocket = null;
                connected = false;

                GamepadClient.Connect(address, port);
            }
        }

        static public void Send(string record)
        {
            if (connected)
            {
                try
                {
                    writer.WriteString(record);
                    writer.StoreAsync();
                }
                catch (Exception)
                {
                    throw new SendingErrorException();
                }
            }
        }

        static public void getCurrentIPAddressAndPort(out string IPAddress, out string port)
        {
            IPAddress = serverHostnameString;
            port = serverPort;
        }
    }
}
