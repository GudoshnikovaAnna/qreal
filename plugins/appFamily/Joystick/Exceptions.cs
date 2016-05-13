using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GamepadClientNamespace
{
    class ConnectionErrorException : Exception
    {
        public ConnectionErrorException() 
        {
        }
        public ConnectionErrorException(string message) : base(message)
        {
        }
        public ConnectionErrorException(string message, Exception inner) : base(message, inner)
        {
        }
    }

    class SendingErrorException : Exception
    {
        public SendingErrorException() 
        {
        }
        public SendingErrorException(string message) : base(message)
        {
        }
        public SendingErrorException(string message, Exception inner) : base(message, inner)
        {
        }
    }
}
