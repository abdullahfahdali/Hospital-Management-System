//===========================HOSPITAL MANAGEMENT SYSTEM==================================
// MADE BY:
//         ABDULLAH FAHD ALI - 25i-6155
// --------------------------------------------------------------------------------------   
// SUBMITTED TO:
//              MS. SANA SALEH
//=======================================================================================
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
using namespace std;

const int MAX = 100;

// Classes
class Patient 
{
private:
    int id;
    string name;
    int age;
    string gender;
    string contact;
    double balance;

public:
    Patient() 
	{ 
		id = 0;
		age = 0;
		balance = 0;
	}
	
    void setId(int x)       
	{ 
		id = x;
	}
    void setName(string x)  
	{ 
		name = x;
	}
    void setAge(int x)      
	{ 
		age = x;
	}
    void setGender(string x)
	{
		gender = x; 
	}
    void setContact(string x)
	{ 
		contact = x;
	}
    void setBalance(double x)
	{ 
		balance = x; 
	}
	
    int getId()      
	{ 
		return id;
	}
    string getName()    
	{ 
		return name; 
	}
    int getAge()
	{ 
		return age; 
	}
    string getGender()  
	{ 
		return gender; 
	}
    string getContact() 
	{ 
		return contact; 
	}
    double getBalance() 
	{ 
		return balance; 
	}
	void display() 
	{
        cout << "ID: " << id << "Name: " << name << "Age: " << age << "Gender: " << gender << "Contact: " << contact << "Balance: Rs. " << balance << endl;
    }
};

class Doctor 
{
private:
    int id;
    string name;
    string specialty;
    int experience;

public:
    Doctor() 
	{ 
		id = 0;
		experience = 0; 
	}

    void setId(int x)          
	{ 
		id = x; 
	}
    void setName(string x)     
	{
		name = x; 
	}
    void setSpecialty(string x)
	{ 
		specialty = x; 
	}
    void setExperience(int x)  
	{ 
		experience = x; 
	}

    int getId()         
	{ 
		return id; 
	}
    string getName()
	{ 
		return name; 
	}
    string getSpecialty()  
	{ 
		return specialty; 
	}
    int getExperience() 
	{ 
		return experience; 
	}

    void display() 
	{
        cout << "ID: " << id << "Name: " << name << "Specialty: " << specialty << "Experience: " << experience << " years" << endl;
    }
};

class Appointment 
{
private:
    int  patientId;
    int  doctorId;
    char date[11];
    char time[10];

public:
    Appointment() 
	{ 
		patientId = 0;
		doctorId = 0; 
	}

    void setPatientId(int x)    
	{ 
		patientId = x; 
	}
    void setDoctorId(int x)     
	{ 
		doctorId = x; 
	}
    void setDate(string x)      
	{ 
		strncpy(date,  x.c_str(), 10); 
		date[10] = '\0'; 
	}
    void setTime(string x)      
	{ 
		strncpy(time, x.c_str(), 9);  
		time[9] = '\0'; 
	}

    int getPatientId() 
	{ 
		return patientId; 
	}
    int getDoctorId()  
	{ 
		return doctorId; 
	}
    string getDate()      
	{ 
		return string(date); 
	}
    string getTime()      
	{ 
		return string(time); 
	}

    void display() 
	{
        cout << "Patient ID: " << patientId << "Doctor ID: " << doctorId << "Date: " << date << "Time: " << time << endl;
    }
};

class Treatment 
{
private:
    int patientId;
    string description;
    double cost;
    bool paid;

public:
    Treatment() 
	{ 
		patientId = 0;
		cost = 0;
		paid = false;
	}

    void setPatientId(int x)      
	{ 
		patientId = x; 
	}
    void setDescription(string x) 
	{ 
		description = x; 
	}
    void setCost(double x)        
	{ 
		cost = x; 
	}
    void setPaid(bool x)          
	{ 
		paid = x; 
	}

    int getPatientId()   
	{ 
		return patientId; 
	}
    string getDescription() 
	{ 
		return description; 
	}
    double getCost()        
	{ 
		return cost; 
	}
    bool isPaid()         
	{ 
		return paid; 
	}

    void display() 
	{
        cout << "Patient ID: " << patientId << "Description: " << description << "Cost: Rs. " << cost << "Status: " << (paid ? "Paid" : "Unpaid") << endl;
    }
};

// Global Arrays
Patient* patients;
Doctor* doctors;
Appointment* appointments;
Treatment* treatments;

int patientCount = 0;
int doctorCount = 0;
int appointmentCount = 0;
int treatmentCount = 0;

// Splitting of a line by '#'
string getField(string line, int index) 
{
    int count = 0;
    string field = "";
    for(int i=0; i<(int)line.size(); i++) 
	{
        if (line[i] == '#') 
		{
            if (count == index) return field;
            count++;
            field = "";
        } 
		else 
		{
            field += line[i];
        }
    }
    if (count == index) 
	{
		return field;
    }
    else
    {
		return "";
	}
}

// Checking if phone number is valid or not
bool isValidPhone(string phone) 
{
    if (phone.size() < 10 || phone.size() > 13) 
	{
		return false;
	}
	for(int i=0; i<(int)phone.size(); i++) 
	{
        if (phone[i] < '0' || phone[i] > '9') 
        {
			return false;
		}
    }
    
    return true;
}

// Fixing gender abbreviation if entered by user
string fixGender(string g) 
{
    if (g == "M" || g == "m") 
	{
		return "Male";
	}
    if (g == "F" || g == "f") 
	{
		return "Female";
	}
	
    return g;
}

// Converting 24-hour time to 12-hour
string fixTime(string t)
{
    bool alreadyFormatted = false;

    // Checking manually for AM
    for(int i = 0; i < (int)t.size()-1; i++)
    {
        if(t[i] == 'A' && t[i+1] == 'M')
        {
            alreadyFormatted = true;
        }
    }

    // Checking manually for PM
    for(int i = 0; i < (int)t.size()-1; i++)
    {
        if(t[i] == 'P' && t[i+1] == 'M')
        {
            alreadyFormatted = true;
        }
    }

    // If already in AM/PM format
    if(alreadyFormatted)
    {
        return t;
    }

    int hour = 0;

    // If format contains :
    bool colonFound = false;

    for(int i = 0; i < (int)t.size(); i++)
    {
        if(t[i] == ':')
        {
            colonFound = true;
        }
    }

    if(colonFound)
    {
        int position = 0;

        for(int i = 0; i < (int)t.size(); i++)
        {
            if(t[i] == ':')
            {
                position = i;
            }
        }

        hour = stoi(t.substr(0, position));

        string mins = t.substr(position + 1);

        string ampm;

        if(hour >= 12)
        {
            ampm = "PM";
        }
        else
        {
            ampm = "AM";
        }

        if(hour > 12)
        {
            hour = hour - 12;
        }

        if(hour == 0)
        {
            hour = 12;
        }

        return to_string(hour) + ":" + mins + " " + ampm;
    }
    else
    {
        hour = stoi(t);

        string ampm;

        if(hour >= 12)
        {
            ampm = "PM";
        }
        else
        {
            ampm = "AM";
        }

        if(hour > 12)
        {
            hour = hour - 12;
        }

        if(hour == 0)
        {
            hour = 12;
        }

        return to_string(hour) + ":00 " + ampm;
    }
}

// Fixing date from YYYY-MM-DD to MM-DD-YYYY
string fixDate(string d) 
{
    if (d.size() == 10 && d[4] == '-') 
	{
        string year = d.substr(0, 4);
        string month = d.substr(5, 2);
        string day = d.substr(8, 2);
        return month + "-" + day + "-" + year;
    }
    
    return d; 
}

// FUNCTION 21: isValidRecord
bool isValidRecord(string id, string name, string contact) 
{
    if (id.empty() || name.empty() || contact.empty()) 
	{
		return false;
	}
    if (!isValidPhone(contact)) 
	{
		return false;
	}
	
    return true;
}

// FUNCTION 22: removeDuplicatePatients
void removeDuplicatePatients() 
{
    ifstream fin("patients.txt");
    if (!fin.is_open()) 
	{
		return;
	}

    string lines[MAX];
    int ids[MAX];
    int total = 0;

    string line;
    while(getline(fin, line) && total<MAX) 
	{
        if (line.empty()) 
		{
			continue;
		}
		
        lines[total] = line;
        string idStr = getField(line, 0);
        ids[total] = idStr.empty() ? -1 : stoi(idStr);
        total++;
    }
    fin.close();

    // Finding which IDs appear more than once
    bool isDuplicate[MAX] = {false};
    for(int i=0; i<total; i++) 
	{
        for(int j=i + 1; j<total; j++) 
		{
            if (ids[i] == ids[j]) 
			{
                isDuplicate[i] = true;
                isDuplicate[j] = true;
            }
        }
    }

    // Writing back only non-duplicates to the patients file
    ofstream fout("patients.txt");
    for (int i = 0; i < total; i++) 
	{
        if (isDuplicate[i]) 
		{
            cout << "Duplicate ID " << ids[i] << " removed.\n";
        } 
		else 
		{
            fout << lines[i] << "\n";
        }
    }
    fout.close();
}

// FUNCTION 19: cleanFile
void cleanFile() 
{
    cout << "\nCleaning data files....\n";

    // --- Clean patients.txt ---
    ifstream fin("patients.txt");
    if (fin.is_open()) 
	{
        string goodLines[MAX];
        int count = 0;
        string line;

        while (getline(fin, line) && count<MAX) 
		{
            if (line.empty()) 
			{
				continue;
			}
			
            string id = getField(line, 0);
            string name = getField(line, 1);
            string age = getField(line, 2);
            string gender = getField(line, 3);
            string contact = getField(line, 4);
            string balance = getField(line, 5);

            // Skipping incomplete records
            if (id.empty() || name.empty() || contact.empty()) 
			{
                cout << "Incomplete record removed.\n";
                
				continue;
            }

            // Skipping invalid phone number
            if (!isValidPhone(contact)) 
			{
                cout << "Invalid phone for ID: " << id << " --> removed.\n";
                
				continue;
            }

            // Fixing gender
            gender = fixGender(gender);
            if (balance.empty())
			{
				balance = "1000";
			}

            goodLines[count++] = id + "#" + name + "#" + age + "#" + gender + "#" + contact + "#" + balance;
            
        }
        fin.close();

        ofstream fout("patients.txt");
        for(int i=0; i<count; i++) 
		{
			fout << goodLines[i] << "\n";
		}
		
        fout.close();
    }

    // Removing duplicates
    removeDuplicatePatients();

    // --- Clean appointments.txt ---
    ifstream afin("appointments.txt");
    if (afin.is_open()) 
	{
        string goodLines[MAX];
        int count = 0;
        string line;

        while(getline(afin, line) && count<MAX) 
		{
            if (line.empty()) 
			{
				continue;
			}
			
            string pid = getField(line, 0);
            string did = getField(line, 1);
            string date = getField(line, 2);
            string time = getField(line, 3);

            date = fixDate(date);
            time = fixTime(time);

            goodLines[count++] = pid + "#" + did + "#" + date + "#" + time;
        }
        afin.close();

        ofstream afout("appointments.txt");
        for(int i=0; i<count; i++) 
		{
			afout << goodLines[i] << "\n";
		}
		
        afout.close();
    }

    cout << "Cleaning done.\n";
}

// Loading all patients from file into array
void loadPatients() 
{
    delete[] patients;
    patients = new Patient[MAX];
    patientCount = 0;

    ifstream fin("patients.txt");
    string line;
    while(getline(fin, line) && patientCount<MAX) 
	{
        if (line.empty()) 
		{
			continue;
		}
		
        patients[patientCount].setId(stoi(getField(line, 0)));
        patients[patientCount].setName(getField(line, 1));
        patients[patientCount].setAge(stoi(getField(line, 2)));
        patients[patientCount].setGender(getField(line, 3));
        patients[patientCount].setContact(getField(line, 4));
        string bal = getField(line, 5);
        patients[patientCount].setBalance(bal.empty() ? 1000 : stod(bal));
        patientCount++;
    }
    
    fin.close();
}

// Loading all doctors from file into array
void loadDoctors() 
{
    delete[] doctors;
    doctors = new Doctor[MAX];
    doctorCount = 0;

    ifstream fin("doctors.txt");
    string line;
    while(getline(fin, line) && doctorCount<MAX) 
	{
        if (line.empty()) 
		{
			continue;
		}
		
        doctors[doctorCount].setId(stoi(getField(line, 0)));
        doctors[doctorCount].setName(getField(line, 1));
        doctors[doctorCount].setSpecialty(getField(line, 2));
        doctors[doctorCount].setExperience(stoi(getField(line, 3)));
        doctorCount++;
    }
    
    fin.close();
}

// Savimg all patients to file
void savePatients() 
{
    ofstream fout("patients.txt");
    for(int i=0; i<patientCount; i++) 
	{
        fout << patients[i].getId() << "#" << patients[i].getName() << "#" << patients[i].getAge() << "#" << patients[i].getGender() << "#" << patients[i].getContact() << "#" << patients[i].getBalance() << "\n";
    }
    
    fout.close();
}

// Saving all doctors to file
void saveDoctors() 
{
    ofstream fout("doctors.txt");
    for(int i=0; i<doctorCount; i++) 
	{
        fout << doctors[i].getId() << "#" << doctors[i].getName() << "#" << doctors[i].getSpecialty() << "#" << doctors[i].getExperience() << "\n";
    }
    
    fout.close();
}

// FIND patient index by ID (-1 if not found)
int findPatient(int id) 
{
    for(int i=0; i<patientCount; i++)
    {
        if (patients[i].getId() == id) 
		{
			return i;
		}
    }
    
    return -1;
}

// FIND doctor index by ID (-1 if not found)
int findDoctor(int id) 
{
    for(int i=0; i<doctorCount; i++)
    {
        if (doctors[i].getId() == id) 
		{
			return i;
		}
    }
    
    return -1;
}

// FUNCTION 1: addPatient
void addPatient() 
{
    cout << "\n--- Add Patient ---\n";

    int id;
    cout << "Enter Patient ID: "; 
	cin >> id; 
	cin.ignore();

    loadPatients();
    if (findPatient(id) != -1) 
	{
        cout << "ID already exists.\n";
        return;
    }

    string name, gender, contact;
    int age;
    double balance;

    cout << "Enter Name: ";
	getline(cin, name);
	
    cout << "Enter Age: "; 
	cin >> age; 
	cin.ignore();
	
    cout << "Enter Gender: "; 
	getline(cin, gender);
	
    cout << "Enter Contact: "; 
	getline(cin, contact);
	
    cout << "Enter Balance (Rs): "; 
	cin >> balance; 
	cin.ignore();

    if (!isValidRecord(to_string(id), name, contact)) 
	{
        cout << "Invalid data! Patient not added.\n";
        
        return;
    }

    gender = fixGender(gender);

    ofstream fout("patients.txt", ios::app);
    fout << id << "#" << name << "#" << age << "#" << gender << "#" << contact << "#" << balance << "\n";
    fout.close();

    cout << "Patient added.\n";
}

// FUNCTION 2: updatePatient
void updatePatient() 
{
    cout << "\n--- Update Patient ---\n";\
    int id;
    cout << "Enter Patient ID: "; 
	cin >> id; 
	cin.ignore();

    loadPatients();
    int idx = findPatient(id);
    if (idx == -1) 
	{ 
		cout << "Patient not found.\n"; 
		return; 
	}

    cout << "Current info:\n"; 
	patients[idx].display();

    string input;
    cout << "\nNew Name (Enter to skip): "; 
	getline(cin, input);
    if (!input.empty()) 
	{
		patients[idx].setName(input);
	}
	
    cout << "New Gender (Enter to skip): "; 
	getline(cin, input);
    if (!input.empty())
	{
		patients[idx].setGender(fixGender(input));
	}

    cout << "New Contact (Enter to skip): "; 
	getline(cin, input);
    if (!input.empty() && isValidPhone(input)) 
	{
		patients[idx].setContact(input);
	}
	
	double bal; 
    cout << "New Balance (-1 to skip): "; 
	cin >> bal; 
	cin.ignore();
	
    if (bal >= 0) 
	{
		patients[idx].setBalance(bal);
	}

    savePatients();
    cout << "Patient updated.\n";
}

// FUNCTION 3: deletePatient
void deletePatient() 
{
    cout << "\n--- Delete Patient ---\n";
    int id;
    cout << "Enter Patient ID: "; 
	cin >> id; 
	cin.ignore();

    loadPatients();
    int idx = findPatient(id);
    if (idx == -1) 
	{ 
		cout << "Patient not found.\n"; 
		return; 
	}

    cout << "Delete this patient?\n"; 
	patients[idx].display();
	char ch;
    cout << "Confirm (y/n): ";  
	cin >> ch; 
	cin.ignore();
    if (ch != 'y') 
	{ 
		cout << "Cancelled.\n"; 
		return; 
	}

    for(int i=idx; i<patientCount-1; i++)
    {
        patients[i] = patients[i + 1];
    }
    patientCount--;

    savePatients();
    cout << "Patient deleted.\n";
}

// FUNCTION 4: viewPatients
void viewPatients() 
{
    cout << "\n--- All Patients ---\n";
    loadPatients();
    if (patientCount == 0) 
	{ 
		cout << "No patients found.\n"; 
		return; 
	}

    for(int i=0; i<patientCount; i++) 
	{
        cout << "-----------------------------\n";
        patients[i].display();
    }
    cout << "-----------------------------\n";
}

// FUNCTION 5: addDoctor
void addDoctor() 
{
	int id;
    cout << "\n--- Add Doctor ---\n";
    cout << "Enter Doctor ID: "; 
	cin >> id; 
	cin.ignore();

    loadDoctors();
    if (findDoctor(id) != -1) 
	{ 
		cout << "Doctor ID already exists.\n"; 
		return; 
	}

    string name, specialty;
    int exp;

    cout << "Enter Name: "; 
	getline(cin, name);
    cout << "Enter Specialty: "; 
	getline(cin, specialty);
    cout << "Enter Experience(yrs): "; 
	cin >> exp; 
	cin.ignore();

    if (name.empty() || specialty.empty()) 
	{
        cout << "Name and specialty required.\n"; 
		return;
    }

    ofstream fout("doctors.txt", ios::app);
    fout << id << "#" << name << "#" << specialty << "#" << exp << "\n";
    fout.close();
    cout << "Doctor added.\n";
}

// FUNCTION 6: updateDoctor
void updateDoctor() 
{
    cout << "\n--- Update Doctor ---\n";
    int id;
    cout << "Enter Doctor ID: "; 
	cin >> id; 
	cin.ignore();

    loadDoctors();
    int idx = findDoctor(id);
    if (idx == -1) 
	{ 
		cout << "Doctor not found.\n"; 
		return; 
	}

    cout << "Current info:\n"; 
	doctors[idx].display();

    string input;
    cout << "\nNew Name (Enter to skip): "; 
	getline(cin, input);
    if (!input.empty())
	{
		doctors[idx].setName(input);
	}

    cout << "New Specialty (Enter to skip): "; 
	getline(cin, input);
    if (!input.empty()) 
	{
		doctors[idx].setSpecialty(input);
	}
	
	int exp;
    cout << "New Experience (-1 to skip): "; 
	cin >> exp; 
	cin.ignore();
    if (exp >= 0) 
	{
		doctors[idx].setExperience(exp);
	}

    saveDoctors();
    cout << "Doctor updated.\n";
}

// FUNCTION 7: deleteDoctor
void deleteDoctor() 
{
    cout << "\n--- Delete Doctor ---\n";
    int id;
    cout << "Enter Doctor ID: "; 
	cin >> id; 
	cin.ignore();

    loadDoctors();
    int idx = findDoctor(id);
    if (idx == -1) 
	{ 
		cout << "Doctor not found.\n"; 
		return; 
	}

    cout << "Delete this doctor?\n"; 
	doctors[idx].display();
    char ch;
    cout << "Confirm (y/n): "; 
	cin >> ch; 
	cin.ignore();
    if (ch != 'y') 
	{ 
		cout << "Cancelled.\n"; 
		return; 
	}

    for(int i=idx; i<doctorCount-1; i++)
    {
        doctors[i] = doctors[i + 1];
    }
    doctorCount--;

    saveDoctors();
    cout << "Doctor deleted.\n";
}

// FUNCTION 8: viewDoctors
void viewDoctors() 
{
    cout << "\n--- All Doctors ---\n";
    loadDoctors();
    if (doctorCount == 0) 
	{ 
		cout << "No doctors found.\n"; 
		return; 
	}

    for(int i=0; i<doctorCount; i++) 
	{
        cout << "-----------------------------\n";
        doctors[i].display();
    }
    cout << "-----------------------------\n";
}

// FUNCTION 9: scheduleAppointment
void scheduleAppointment() 
{
    cout << "\n--- Schedule Appointment ---\n";

    int pid, did;
    cout << "Enter Patient ID: "; 
	cin >> pid; 
	cin.ignore();
	
    cout << "Enter Doctor  ID: "; 
	cin >> did; 
	cin.ignore();

    loadPatients();
    loadDoctors();

    int pidx = findPatient(pid);
    int didx = findDoctor(did);

    if (pidx == -1) 
	{ 
		cout << "Patient not found.\n"; 
		return; 
	}
    if (didx == -1) 
	{ 
		cout << "Doctor not found.\n";  
		return; 
	}

    double fee;
    cout << "Consultation fee (Rs): "; 
	cin >> fee; 
	cin.ignore();

    // Checking balance
    if (patients[pidx].getBalance() < fee) 
	{
        cout << "Insufficient balance (Rs. " << patients[pidx].getBalance() << "). Needed: Rs. " << fee << ". Appointment denied.\n";
        return;
    }

    string date, time;
    cout << "Enter Date (MM-DD-YYYY): "; 
	getline(cin, date);
	
    cout << "Enter Time (e.g. 10:00 AM): ";
	getline(cin, time);

    date = fixDate(date);
    time = fixTime(time);

    // Checking if slot is already taken
    ifstream fin("appointments.txt");
    string line;
    while(getline(fin, line)) 
	{
        if (line.empty()) 
		{
			continue;
        }
        
		string d = getField(line, 1);
        string dt = getField(line, 2);
        string tm = getField(line, 3);
        if (stoi(d) == did && dt == date && tm == time) 
		{
            cout << "This slot is already booked. Please choose another time.\n";
            fin.close();
            return;
        }
    }
    fin.close();

    // Deduct fee
    patients[pidx].setBalance(patients[pidx].getBalance() - fee);
    savePatients();

    // Save appointment
    ofstream fout("appointments.txt", ios::app);
    fout << pid << "#" << did << "#" << date << "#" << time << "\n";
    fout.close();

    // Save to bills
    ofstream bout("bills.txt", ios::app);
    bout << pid << "#" << fee << "#Paid\n";
    bout.close();

    cout << "Appointment scheduled on " << date << " at " << time << ".\n";
    cout << "Rs. " << fee << " deducted. New balance: Rs. " << patients[pidx].getBalance() << "\n";
}

// FUNCTION 10: cancelAppointment
void cancelAppointment() 
{
    cout << "\n--- Cancel Appointment ---\n";

    int pid, did;
    string date;
    cout << "Enter Patient ID: "; 
	cin >> pid; 
	cin.ignore();
	
    cout << "Enter Doctor ID: "; 
	cin >> did; 
	cin.ignore();
	
    cout << "Enter Date (MM-DD-YYYY): "; 
	getline(cin, date);

    ifstream fin("appointments.txt");
    string remaining[MAX];
    int count = 0;
    bool found = false;
    string line;

    while(getline(fin, line)) 
	{
        if (line.empty()) 
		{
			continue;
        }
        
		int p = stoi(getField(line, 0));
        int d = stoi(getField(line, 1));
        string dt = getField(line, 2);
        if (p == pid && d == did && dt == date) 
		{
            found = true;
            cout << "Appointment cancelled.\n";
        } 
		else 
		{
            remaining[count++] = line;
        }
    }
    
    fin.close();

    if (!found) 
	{ 
		cout << "Appointment not found.\n"; 
		return; 
	}

    ofstream fout("appointments.txt");
    for(int i=0; i<count; i++) 
	{
		fout << remaining[i] << "\n";
	}
	
    fout.close();
}

// FUNCTION 11: viewAppointments
void viewAppointments() 
{
    cout << "\n--- All Appointments ---\n";

    ifstream fin("appointments.txt");
    string line;
    int count = 0;

    while (getline(fin, line)) 
	{
        if (line.empty()) 
		{
			continue;
		}
		
        count++;
        cout << "-----------------------------\n";
        cout << "Patient ID: " << getField(line, 0) << endl;
        cout << "Doctor ID: " << getField(line, 1) << endl;
        cout << "Date: " << getField(line, 2) << endl;
        cout << "Time: " << getField(line, 3) << endl;
    }
    fin.close();

    if (count == 0) 
	{
		cout << "No appointments found.\n";
	}
    else 
	{
		cout << "-----------------------------\n";
	}
}

// FUNCTION 12: addTreatment
void addTreatment() 
{
    cout << "\n--- Add Treatment ---\n";

    int pid;
    cout << "Enter Patient ID: "; 
	cin >> pid; 
	cin.ignore();

    loadPatients();
    if (findPatient(pid) == -1) 
	{ 
		cout << "Patient not found.\n"; 
		return; 
	}

    string desc;
    double cost;
    char paidChar;

    cout << "Enter Treatment Details: "; 
	getline(cin, desc);
    
	cout << "Enter Cost (Rs): "; 
	cin >> cost; 
	cin.ignore();
    
	cout << "Bill paid? (y/n): "; 
	cin >> paidChar; 
	cin.ignore();

    string paidStr = (paidChar == 'y') ? "true" : "false";
    string billStr = (paidChar == 'y') ? "Paid" : "Unpaid";

    ofstream fout("treatments.txt", ios::app);
    fout << pid << "#" << desc << "#" << cost << "#" << paidStr << "\n";
    fout.close();

    ofstream bout("bills.txt", ios::app);
    bout << pid << "#" << cost << "#" << billStr << "\n";
    bout.close();

    cout << "Treatment added.\n";
}

// FUNCTION 13: updatePayment
void updatePayment() 
{
    cout << "\n--- Update Payment Status ---\n";
    int pid;
    cout << "Enter Patient ID: ";
	cin >> pid; 
	cin.ignore();

    // Update treatments.txt
    ifstream fin("treatments.txt");
    string lines[MAX];
    int count = 0;
    bool found = false;
    string line;

    while(getline(fin, line) && count<MAX) 
	{
        if (line.empty()) 
		{
			continue;
		}
		
        int id = stoi(getField(line, 0));
        string status = getField(line, 3);
        if (id == pid && status == "false") 
		{
            // Replacing "false" with "true"
            string newLine = getField(line,0) + "#" + getField(line,1) + "#" + getField(line,2) + "#true";
            lines[count++] = newLine;
            found = true;
            cout << "Marked paid: " << getField(line,1) << "\n";
        } 
		else 
		{
            lines[count++] = line;
        }
    }
    fin.close();

    if (!found) 
	{ 
		cout << "No unpaid treatments for patient " << pid << ".\n"; 
		return; 
	}

    ofstream fout("treatments.txt");
    for(int i=0; i<count; i++) 
	{
		fout << lines[i] << "\n";
	}
    fout.close();

    // Update bills.txt
    ifstream bfin("bills.txt");
    string blines[MAX];
    int bcount = 0;
    while(getline(bfin, line) && bcount<MAX) 
	{
        if (line.empty()) 
		{
			continue;
		}
		
        int id = stoi(getField(line, 0));
        string status = getField(line, 2);
        if (id == pid && status == "Unpaid") 
		{
            blines[bcount++] = getField(line,0) + "#" + getField(line,1) + "#Paid";
        } 
		else 
		{
            blines[bcount++] = line;
        }
    }
    
    bfin.close();

    ofstream bfout("bills.txt");
    for(int i=0; i<bcount; i++) 
	{
		bfout << blines[i] << "\n";
	}
	
    bfout.close();

    cout << "Payment updated to Paid.\n";
}

// FUNCTION 14: viewTreatments
void viewTreatments() 
{
    cout << "\n--- View Treatments ---\n";
    int pid;
    cout << "Enter Patient ID (0 = all): ";  
	cin >> pid; 
	cin.ignore();

    ifstream fin("treatments.txt");
    string line;
    int count = 0;

    while(getline(fin, line)) 
	{
        if (line.empty()) 
		{
			continue;
		}
		
        int id = stoi(getField(line, 0));
        if (pid != 0 && id != pid) 
		{
			continue;
		}
		
        count++;
        cout << "-----------------------------\n";
        cout << "Patient ID: " << getField(line, 0) << endl;
        cout << "Description: " << getField(line, 1) << endl;
        cout << "Cost: Rs. " << getField(line, 2) << endl;
        string s = getField(line, 3);
        cout << "Status: " << (s == "true" ? "Paid" : "Unpaid") << endl;
    }
    
    fin.close();

    if (count == 0)
	{
		cout << "No treatments found.\n";
	}
    else 
	{
		cout << "-----------------------------\n";
	}
}

// FUNCTION 15: generateBill
void generateBill() 
{
    cout << "\n--- Generate Bill ---\n";
    int pid;
    cout << "Enter Patient ID: "; 
	cin >> pid; 
	cin.ignore();

    loadPatients();
    int pidx = findPatient(pid);
    if (pidx == -1) 
	{ 
		cout << "Patient not found.\n"; 
		return; 
	}

    cout << "\n========================================\n";
    cout << "            HOSPITAL BILL\n";
    cout << "  Patient : " << patients[pidx].getName() << " (ID: " << pid << ")\n";
    cout << "========================================\n";

    // Printing treatments and sum total
    ifstream fin("treatments.txt");
    string line;
    double total = 0, unpaid = 0;

    cout << "  Treatments:\n";
    while(getline(fin, line)) 
	{
        if (line.empty()) 
		{
			continue;
		}
        if (stoi(getField(line, 0)) != pid) 
		{
			continue;
		}
		
        double cost = stod(getField(line, 2));
        string status = getField(line, 3);
        total = total + cost;
        if (status == "false") 
		{
			unpaid = unpaid + cost;
		}
        cout << "  - " << getField(line, 1) << " : Rs. " << cost << " [" << (status == "true" ? "Paid" : "Unpaid") << "]\n";
    }
    fin.close();

    cout << "\nTotal: Rs. " << total  << endl;
    cout << "Unpaid: Rs. " << unpaid << endl;
    cout << "========================================\n";
}

// FUNCTION 16: searchPatientsBydoc_ID
void searchPatientsBydoc_ID() 
{
    cout << "\n--- Search Patients ---\n";
    int ch;
    cout << "1. By ID\n2. By Name\nChoice: ";
    cin >> ch; 
	cin.ignore();

    loadPatients();
    bool found = false;

    if (ch == 1) 
	{
		int id;
        cout << "Enter Patient ID: "; 
		cin >> id; 
		cin.ignore();
        for(int i=0; i<patientCount; i++) 
		{
            if (patients[i].getId() == id) 
			{
                patients[i].display();
                found = true;
            }
        }
    } 
	else 
	{
		string name;
        cout << "Enter Name: ";
		getline(cin, name);
        for(int i=0; i<patientCount; i++) 
		{
            if (patients[i].getName() == name)
			{
                cout << "-----------------------------\n";
                patients[i].display();
                found = true;
            }
        }
    }

    if (!found) cout << "No match found.\n";
}

// FUNCTION 17: searchDoctorBySpecialty
void searchDoctorBySpecialty() 
{
    cout << "\n--- Search Doctors ---\n";
    int ch;
    cout << "1. By ID\n2. By Specialty\nChoice: ";
    cin >> ch; 
	cin.ignore();

    loadDoctors();
    bool found = false;

    if (ch == 1) 
	{
		int id;
        cout << "Enter Doctor ID: "; 
		cin >> id; 
		cin.ignore();
        for(int i=0; i<doctorCount; i++) 
		{
            if (doctors[i].getId() == id) 
			{
                doctors[i].display();
                found = true;
            }
        }
    } 
	else 
	{
		string spec;
        cout << "Enter Specialty: "; 
		getline(cin, spec);
        for(int i=0; i<doctorCount; i++) 
		{
            if (doctors[i].getSpecialty() == spec)
			{
                cout << "-----------------------------\n";
                doctors[i].display();
                found = true;
            }
        }
    }

    if (!found) cout << "No match found.\n";
}

// FUNCTION 18: viewTreatmentsByDoctor
void viewTreatmentsByDoctor() 
{
    cout << "\n--- Treatments by Doctor ---\n";
    int did;
    cout << "Enter Doctor ID: "; 
	cin >> did; 
	cin.ignore();

    loadDoctors();
    int didx = findDoctor(did);
    if (didx == -1) 
	{ 
		cout << "Doctor not found.\n"; 
		return; 
	}

    cout << "Doctor: " << doctors[didx].getName() << "\n\n";

    // 1. Finding all patient IDs who had appointments with this doctor
    int patIds[MAX];
    int patCount = 0;

    ifstream afin("appointments.txt");
    string line;
    while (getline(afin, line)) 
	{
        if (line.empty()) 
		{
			continue;
		}
        if (stoi(getField(line, 1)) == did) 
		{
            patIds[patCount++] = stoi(getField(line, 0));
        }
    }
    afin.close();

    if (patCount == 0) 
	{ 
		cout << "No patients found for this doctor.\n"; 
		return; 
	}

    // 2. Showing treatments for those patients
    ifstream tfin("treatments.txt");
    int count = 0;
    while (getline(tfin, line)) 
	{
        if (line.empty()) 
		{
			continue;
		}
        int tpid = stoi(getField(line, 0));
        for(int i=0; i<patCount; i++) 
		{
            if (patIds[i] == tpid) 
			{
                count++;
                cout << "-----------------------------\n";
                cout << "Patient ID: " << getField(line, 0) << endl;
                cout << "Description: " << getField(line, 1) << endl;
                cout << "Cost: Rs. " << getField(line, 2) << endl;
                string s = getField(line, 3);
                cout << "Status: " << (s == "true" ? "Paid" : "Unpaid") << endl;
                break;
            }
        }
    }
    tfin.close();

    if (count == 0) 
	{
		cout << "No treatments found.\n";
    }
	else 
	{
		cout << "-----------------------------\n";
	}
}

// FUNCTION 20: sortDoctorsByExperience
void sortDoctorsByExperience() 
{
    cout << "\n--- Doctors Sorted by Experience ---\n";
    loadDoctors();

    for(int i=0; i<doctorCount-1; i++) 
	{
        for(int j=0; j<doctorCount-i-1; j++) 
		{
            if (doctors[j].getExperience() < doctors[j+1].getExperience()) 
			{
                Doctor temp = doctors[j];
                doctors[j] = doctors[j+1];
                doctors[j+1] = temp;
            }
        }
    }

    for(int i=0; i<doctorCount; i++) 
	{
        cout << "-----------------------------\n";
        cout << "Rank " << (i+1) << ":\n";
        doctors[i].display();
    }
    cout << "-----------------------------\n";
}

// Weekly Schedule
void weeklySchedule() 
{
    cout << "\n--- Weekly Schedule ---\n";
    int did;
    cout << "Enter Doctor ID: "; 
	cin >> did; 
	cin.ignore();

    loadDoctors();
    if (findDoctor(did) == -1) 
	{ 
		cout << "Doctor not found.\n"; 
		return; 
	}

    const int DAYS = 7, SLOTS = 6;
    string days[DAYS]  = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
    string slots[SLOTS]= {"08:00 AM","09:00 AM","10:00 AM","11:00 AM","01:00 PM","02:00 PM"};
    string schedule[DAYS][SLOTS];

    for(int d=0; d<DAYS; d++)
        for(int s=0; s<SLOTS; s++)
        {
			schedule[d][s] = "Free ";
		}

    ifstream fin("appointments.txt");
    string line;
    while(getline(fin, line)) 
	{
        if (line.empty()) 
		{
			continue;
		}
        if (stoi(getField(line, 1)) != did) 
		{
			continue;
		}
        string t = getField(line, 3);
        for(int s=0; s<SLOTS; s++) 
		{
            if (slots[s] == t) schedule[0][s] = " Booked ";
        }
    }
    fin.close();

    cout << "\n" << left << setw(12) << "Time";
    for(int d=0; d<DAYS; d++) 
	{
		cout << setw(10) << days[d];
	}
    cout << "\n" << string(82, '-') << "\n";
    for(int s=0; s<SLOTS; s++) 
	{
        cout << left << setw(12) << slots[s];
        for(int d=0; d<DAYS; d++) 
		{
			cout << setw(10) << schedule[d][s];
		}
        cout << "\n";
    }
}

// Creating sample files if missing
void createSampleFiles() 
{
    ifstream test("patients.txt");
    if (test.is_open()) 
	{ 
		test.close(); 
		return; 
	} 

    ofstream pout("patients.txt");
    pout << "101#Ali Raza#25#Male#03001234567#2000\n"
      << "102#Sara Ahmed#30#Female#03009876543#5000\n"
      << "103#Usman Khan#40#Male#03211234567#1500\n"
      << "104#Fatima Malik#22#F#0300123\n"     
      << "101#Hassan Ali#28#Male#03451234567#3000\n"; 
    pout.close();

    ofstream dout("doctors.txt");
    dout << "201#Dr. Kamran#Cardiologist#10\n"
      << "202#Dr. Sana#ENT#5\n"
      << "203#Dr. Imran#Neurologist#8\n";
    dout.close();

    ofstream aout("appointments.txt");
    aout << "101#201#2026-03-30#10:00 AM\n"
      << "102#202#2026-03-31#02:00 PM\n";
    aout.close();

    ofstream tout("treatments.txt");
    tout << "101#Heart Checkup#5000#true\n"
      << "102#Ear Surgery#15000#false\n";
    tout.close();

    ofstream bout("bills.txt");
    bout << "101#5000#Paid\n"
      << "102#15000#Unpaid\n";
    bout.close();
}


// Login
bool login() 
{
    string id, pass;
    cout << "Enter Employee ID: "; 
	cin >> id;
    cout << "Enter Password: ";
	cin >> pass;
    cin.ignore();
    if (id == "123" && pass == "pass123") 
	{
        cout << "\nLogin Successful!\n";
        return true;
    }
    cout << "Wrong ID or Password.\n";
    return false;
}


void patientMenu() 
{
    int ch;
    do 
	{
        cout << "\n--- Patient Management ---\n" << "1. Add Patient\n2. Update Patient\n" << "3. Delete Patient\n4. View All Patients\n0. Back\nChoice: ";
        cin >> ch; 
		cin.ignore();
        if (ch == 1) 
		{
			addPatient();
		}
        else if (ch == 2) 
		{
			updatePatient();
		}
        else if (ch == 3) 
		{
			deletePatient();
		}
        else if (ch == 4) 
		{
			viewPatients();
		}
    } while (ch != 0);
}

void doctorMenu() 
{
    int ch;
    do {
        cout << "\n--- Doctor Management ---\n" << "1. Add Doctor\n2. Update Doctor\n" << "3. Delete Doctor\n4. View All Doctors\n0. Back\nChoice: ";
        cin >> ch; cin.ignore();
        if (ch == 1) 
		{
			addDoctor();
		}
        else if (ch == 2) 
		{
			updateDoctor();
		}
        else if (ch == 3) 
		{
			deleteDoctor();
		}
        else if (ch == 4) 
		{
			viewDoctors();
		}
    } while (ch != 0);
}

void appointmentMenu() 
{
    int ch;
    do {
        cout << "\n--- Appointments ---\n" << "1. Schedule Appointment\n2. Cancel Appointment\n" << "3. View All Appointments\n4. Weekly Schedule (Bonus)\n0. Back\nChoice: ";
        cin >> ch; 
		cin.ignore();
        if      (ch == 1) scheduleAppointment();
        else if (ch == 2) cancelAppointment();
        else if (ch == 3) viewAppointments();
        else if (ch == 4) weeklySchedule();
    } while (ch != 0);
}

void treatmentMenu() {
    int ch;
    do {
        cout << "\n--- Treatments & Billing ---\n" << "1. Add Treatment\n2. View Treatments\n" << "3. Update Payment\n4. Generate Bill\n0. Back\nChoice: ";
        cin >> ch; 
		cin.ignore();
        if(ch == 1) 
		{
			addTreatment();
		}
        else if (ch == 2) 
		{
			viewTreatments();
		}
        else if (ch == 3) 
		{
			updatePayment();
		}
        else if (ch == 4) 
		{
			generateBill();
		}
    } while (ch != 0);
}

void searchMenu() 
{
    int ch;
    do {
        cout << "\n--- Search / Reports ---\n"
             << "1. Search Patient (ID or Name)\n"
             << "2. Search Doctor  (ID or Specialty)\n"
             << "3. Treatments by Doctor\n"
             << "4. Generate Bill\n"
             << "5. Sort Doctors by Experience\n"
             << "0. Back\nChoice: ";
        cin >> ch; 
		cin.ignore();
        if (ch == 1) 
		{
			searchPatientsBydoc_ID();
		}
        else if (ch == 2) 
		{
			searchDoctorBySpecialty();
		}
        else if (ch == 3) 
		{
			viewTreatmentsByDoctor();
		}
        else if (ch == 4) 
		{
			generateBill();
		}
        else if (ch == 5) 
		{
			sortDoctorsByExperience();
		}
    } while (ch != 0);
}

int main() 
{

    patients = new Patient[MAX];
    doctors = new Doctor[MAX];
    appointments = new Appointment[MAX];
    treatments = new Treatment[MAX];

    cout << "========================================\n";
    cout << "     HOSPITAL MANAGEMENT SYSTEM\n";
    cout << "========================================\n";

    createSampleFiles();


    cleanFile();

    cout << "\nPlease login:\n";
    int tries = 0;
    bool loggedIn = false;
    while (tries < 3 && !loggedIn) 
	{
        loggedIn = login();
        tries++;
    }
    if (!loggedIn) 
	{ 
		cout << "Too many failed attempts. Exiting.\n"; 
		return 0; 
	}
    int choice;
    do {
        cout << "\n======== Main Menu ========\n"
             << "1. Patient Management\n"
             << "2. Doctor Management\n"
             << "3. Appointments\n"
             << "4. Treatments & Billing\n"
             << "5. Search / Reports\n"
             << "6. Exit\n"
             << "===========================\n"
             << "Choice: ";
        cin >> choice; cin.ignore();

        if (choice == 1) 
		{
			patientMenu();
		}
        else if (choice == 2) 
		{
			doctorMenu();
		}
        else if (choice == 3) 
		{
			appointmentMenu();
		}
        else if (choice == 4) 
		{
			treatmentMenu();
		}
        else if (choice == 5) 
		{
			searchMenu();
		}
        else if (choice == 6) 
		{
			cout << "\nWishing you a nice health!\n";
		}
        else 
		{
			cout << "Invalid choice.\n";
		}

    } while (choice != 6);

    delete[] patients;
    delete[] doctors;
    delete[] appointments;
    delete[] treatments;

    return 0;
}

