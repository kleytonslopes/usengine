using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassCreator.Data
{
    public class FileDescriptor
    {
        public FileDescriptor() { }

        public FileDescriptor(Dir dir, string fullName)
        {
            Dir = dir;
            FullName = fullName;
            Name = fullName.Replace($"{dir.FullName}\\", "");
            Extension = Name.Split('.')[1];

            if (Name.Contains('-'))
                IsGenerated = true;
        }

        public string Name { get; set; }
        public string FullName { get; set; }
        public string Extension { get; set; }
        public bool IsGenerated { get; set; }
        public Dir Dir { get; set; }
    }
}
