using System;

namespace InheritenceCsharp
{
    class MainClass
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Hello World!\n");
            Doctor Doc = new Doctor("UCSF", "Robert", 45, 15);
            Oncologist OncDoc = new Oncologist("Hematology Oncology", "UCSF", "Barbara", 67, 30);
            ENT ent = new ENT("adults", "Standford", "Tom", 45, 12);
            Surgeon entsurg = new Surgeon("ears", "Duke", "Benjamin", 42, 9);
            Radiologist radio = new Radiologist("Female", "Alta Bates", "Christine", 42, 7);

            Doc.Intro();
            Console.Write("\n");
            OncDoc.IntroExtend();
            ent.IntroExtend();
            entsurg.IntroExtend();
            radio.IntroExtend();

        }
    }

    class Doctor
    {
        private string Hospital;
        private string Name;
        private int Age;
        private int YearsInPractice;

        public Doctor()
        {
            Hospital = "UCSF Benioff Children\'s";
            Console.WriteLine("Unknown Doctor @ Children's Hospital");
        }

        public Doctor(string Hosp, string name, int age, int years)
        {
            Hospital = Hosp;
            Name = name;
            Age = age;
            YearsInPractice = years;
        }

        public void Intro()
        {
            Console.WriteLine($"My name is {Name} and I'm {Age} years old. I'm a doctor at {Hospital} with {YearsInPractice} " +
                $"experience.");
        }
    }

    class Oncologist : Doctor
    {
        private string Branch;

        public Oncologist()
        {
            Console.WriteLine("Uknown Oncologist");
        }

        public Oncologist(string specialty, string Hosp, string name, int age, int years)
            : base(Hosp, name, age, years)
        {
            Branch = specialty;
        }

        public void IntroExtend()
        {
            this.Intro();
            Console.WriteLine($"The branch that I am in is {Branch}.\n");
        }

    }

    class ENT : Doctor
    {
        private string AgeClass;

        public ENT()
        {
            Console.WriteLine("Uknown ENT (Ears, Nose, Throat)");
        }

        public ENT(string group, string Hosp, string name, int age, int years)
            : base(Hosp, name, age, years)
        {
            AgeClass = group;
        }

        virtual public void IntroExtend()
        {
            this.Intro();
            Console.WriteLine($"I specialize in the ears, nose, and throat for {AgeClass}.\n");
        }
    }

    class Surgeon : ENT
    {
        private string DisorderArea;

        public Surgeon()
        {
            Console.WriteLine("Uknown ENT Surgeon");
        }

        public Surgeon(string DisType, string Hosp, string name, int age, int years)
            : base("Children", Hosp, name, age, years)
        {
            DisorderArea = DisType;
        }

        public override void IntroExtend()
        {
            this.Intro();
            Console.WriteLine($"I am an ENT surgeon practicing in the {DisorderArea} area.\n");
        }

    }

    class Radiologist : Doctor
    {
        private string Gender;

        public Radiologist()
        {
            Console.WriteLine("Uknown Radiologist");
        }

        public Radiologist(string gender, string Hosp, string name, int age, int years)
            : base(Hosp, name, age, years)
        {
            Gender = gender;
        }

        public void IntroExtend()
        {
            this.Intro();
            Console.WriteLine($"I am a radiologist who treats {Gender}.\n");
        }

    }
}
