using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Input;

namespace GamepadSemester
{
    class RecordMaker
    {
        private static string MakeDPadRecordBeginning(string dPadName)
        {
            string beginning = "dPad ";

            if (dPadName == "dPad1")
            {
                beginning += "1 ";
            }
            else
            {
                beginning += "2 ";
            }

            return beginning;
        }

        public static string MakeDPadPressRecord(PointerPoint point, string dPadName)
        {
            string record = MakeDPadRecordBeginning(dPadName);

            double pointX = (point.Position.X / 130) * 200 - 100;
            double pointY = (point.Position.Y / 130) * 200 - 100;

            record += Convert.ToInt32(pointX).ToString() + " " + Convert.ToInt32(pointY).ToString() + '\n';

            return record;
        }

        public static string MakeDPadReleaseRecord(string dPadName)
        {
            string record = MakeDPadRecordBeginning(dPadName);

            record += "up" + '\n';

            return record;
        }

        public static string MakeButtonPressedRecord(int buttonId)
        {
            return "btn " + buttonId.ToString() + '\n';
        }
    }
}
