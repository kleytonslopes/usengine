using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassCreator.Data
{
    public class ClassData
    {
        public bool HasGen { get; set; }
        public bool HasCpp { get; set; }
        /// <summary>
        /// UClassName
        /// </summary>
        public string ClassName { get; set; }
        
        /// <summary>
        /// US_CLASS_NAME_HPP
        /// </summary>
        public string ClassDefinition { get; set; }

        /// <summary>
        /// ClassName.hpp
        /// </summary>
        public string HppFileName { get; set; }

        /// <summary>
        /// ClassName.cpp
        /// </summary>
        public string CppFileName { get; set; }

        /// <summary>
        /// ClassName-generated.hpp
        /// </summary>
        public string GenFileName { get; set; }

        /// <summary>
        /// include/Class/Test
        /// </summary>
        public string FolderHpp { get; set; }

        /// <summary>
        /// src/Class/Test
        /// </summary>
        public string FolderCpp { get; set;}

        /// <summary>
        /// generated
        /// </summary>
        public string FolderGen { get; set; }

        /// <summary>
        /// July 23
        /// </summary>
        public string DateCreation { get; set;}

        /// <summary>
        /// UClassBaseName
        /// </summary>
        public string BaseClassName { get; set; }

        /// <summary>
        /// Base/ClassBaseName.hpp
        /// </summary>
        public string BaseClassPathHpp { get; set;}

        /// <summary>
        /// : public UClassBaseName
        /// </summary>
        public string BaseClassTemplate { get; set;}

        /// <summary>
        /// #include "Base/ClassBaseName.hpp"
        /// </summary>
        public string BaseClassInclude { get; set; }

        /// <summary>
        /// hpp_UClassName_UClassBaseName
        /// </summary>
        public string ClassGenDefinition { get; set; }

        /// <summary>
        /// hpp_UClassName_UClassBaseName_default
        /// </summary>
        public string ClassGenDefinitionVersion { get; set; }

        /// <summary>
        /// HeadClass/ClassTest.hpp
        /// </summary>
        /// <returns></returns>
        public string GetClassHeadPath()
        {
            return $"{FolderHpp.Replace("include/", "")}/{HppFileName}";
        }
        /// <summary>
        /// using Super = UClassBase; 
        /// </summary>
        /// <returns></returns>
        public string GetSuperTemplate()
        {
            if (string.IsNullOrWhiteSpace(BaseClassName))
                return string.Empty;

            return $"using Super = {BaseClassName}; ";
        }

        public string GetGenBobdy()
        {
            if (HasGen)
                return "DEFAULT_BODY_GENERATED()";

            return string.Empty;
        }

        public string GetGenInclude()
        {
            if (!HasGen) return string.Empty;

            return $"\n#include \"{GenFileName}\"";
        }
    }
}
