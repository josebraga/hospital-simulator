#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

#include "patient.h"

Condition convertInputToCondition(const std::string& condition)
{
  if (condition == "H")
    return Condition::HEALTHY;
  else if (condition == "F")
      return Condition::FEVER;
  else if (condition == "D")
      return Condition::DIABETES;
  else if (condition == "T")
      return Condition::TUBERCULOSIS;
  else if (condition == "X")
      return Condition::DEAD;

  throw std::runtime_error("wrong input for condition");
}

Drugs convertInputToDrug(const std::string& drug)
{
  if (drug == "An")
    return Drugs::ANTIBIOTIC;
  else if (drug == "As")
    return Drugs::ASPIRIN;
  else if (drug == "I")
    return Drugs::INSULIN;
  else if (drug == "P")
    return Drugs::PARACETAMOL;

  throw std::runtime_error("wrong input for drug");
}

std::vector<Patient> decodePatients(const char* input)
{
  std::string input_string {input};

  std::vector<Patient> tokens;
  std::string token;

  std::istringstream tokenStream(input_string);

  while (std::getline(tokenStream, token, ','))
  {
    tokens.push_back(Patient(convertInputToCondition(token)));
  }

  return std::move(tokens);
}

std::set<Drugs> decodeDrugs(const char* input = "")
{
  std::string input_string {input};

  std::set<Drugs> tokens;
  std::string token;

  std::istringstream tokenStream(input_string);

  while (std::getline(tokenStream, token, ','))
  {
    tokens.insert(convertInputToDrug(token));
  }

  return std::move(tokens);
}

void toOutput(const std::vector<Patient>& patient_list)
{
  int array[Condition::TOTAL] = {0};

  for (const auto& patient : patient_list )
  {
    array[patient.getState()]++;
  }

  // print result to output.
  std::printf("F:%d,H:%d,D:%d,T:%d,X:%d\n\n",
              array[Condition::FEVER],
              array[Condition::HEALTHY],
              array[Condition::DIABETES],
              array[Condition::TUBERCULOSIS],
              array[Condition::DEAD]);
}

int main(int argc, char** argv)
{
  if (argc != 2 && argc != 3)
  {
    std::cerr << "wrong number of arguments!" << std::endl;
    return 1;
  }

  try
  {
    std::vector<Patient> patient_list = decodePatients(argv[1]);
    std::set<Drugs> drugs = (argc == 3) ? decodeDrugs(argv[2]): decodeDrugs();

    for (auto& patient : patient_list)
    {
      patient.takes(drugs);
    }

    toOutput(patient_list);
  }
  catch (std::runtime_error &e)
  {
    std::cerr << "runtime_error exception: " << e.what () << std::endl;
    return 2;
  }

  return 0;
}
