using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace Kyrnness.Data
{
    public class ClassObject
    {
        public ClassObject() { }

        public string Name { get; set; } = "Invalid Class";
        public string Prefix { get; set; } = "Invalid Class";

        public bool CanInherit { get; set; }
        public bool Inline { get; set; }
        public bool HasCpp { get; set; }

        public bool HasPragmaOnce { get; set; } = true;
        public bool HasDefinition { get; set; } = true;
        public bool HasGeneratedBody { get; set; } = true;
        public bool HasCopyright { get; set; } = true;

        public ClassObject BaseClass { get; set; }
        public FolderObject Folder { get; set; }

        public string ClassObjectName => $"{Prefix}{Name}";
        public string HppFileName
        {
            get
            {
                return $"{Name}.hpp";
            }
        }
        public string CppFileName
        {
            get
            {
                return $"{Name}.cpp";
            }
        }
        public string IncludePath
        {
            get
            {
                string hppFIle = HppFileName;
                return $"{Folder.Path}/{hppFIle}";
            }
        }
        public string GenneratedHppFileName
        {
            get
            {
                return $"{Name}-defaults.hpp";
            }
        }
        public string ClassDefinition
        {
            get
            {
                return $"US_{Regex.Replace(Name, "([a-z])([A-Z])", "$1_$2")}_HPP".ToUpper();
            }
        }
        public string GenerateDefinition => $"DEFAULTS_{Regex.Replace(Name, "([a-z])([A-Z])", "$1_$2")}_HPP".ToUpper();

    }
}
