#ifndef SYONE_HOSPITAL_PATIENT_H
#define SYONE_HOSPITAL_PATIENT_H

#include <string>
#include <set>
#include <random>
#include <iostream>

/* List of possible conditions a patient may have */
enum Condition
{
  HEALTHY,
  FEVER,
  DIABETES,
  TUBERCULOSIS,
  DEAD,
  TOTAL
};

/* List of drugs to be administered */
enum Drugs
{
  ASPIRIN,
  ANTIBIOTIC,
  INSULIN,
  PARACETAMOL
};

class Patient
{
public:
  Patient(Condition condition, unsigned int odds = 1000000):
    current_state(condition),
    current_drugs(nullptr),
    m_odds(odds)
  { }

  void takes(const std::set<Drugs>& drugs)
  {
    current_drugs = &drugs;
    process();
  }

  Condition getState() const
  {
    return current_state;
  }

private:
  Condition current_state;
  const std::set<Drugs>* current_drugs;
  unsigned int m_odds;

  void process()
  {
    // general case.
    if (deadCombo())
    {
      current_state = Condition::DEAD;
      return;
    }

    // state machine approach.
    switch (current_state)
    {
      case Condition::HEALTHY:
        if (contains(Drugs::INSULIN) && contains(Drugs::ANTIBIOTIC))
          current_state = FEVER;

        break;
      case Condition::FEVER:
        if (contains(Drugs::ASPIRIN) || contains(Drugs::PARACETAMOL))
          current_state = Condition::HEALTHY;

        break;
      case Condition::DIABETES:
        if (!contains(Drugs::INSULIN))
          current_state = Condition::DEAD;

        break;
      case Condition::TUBERCULOSIS:
        if (contains(Drugs::ANTIBIOTIC))
          current_state = Condition::HEALTHY;

        break;
      case Condition::DEAD:
        if (reallyLucky())
          current_state = Condition::HEALTHY;

        break;
      default:
        // do nothing or throw error
        break;
    }
  }

  bool deadCombo() const
  {
    if (contains(Drugs::PARACETAMOL) && contains(Drugs::ASPIRIN))
      return true;

    return false;
  }

  bool contains(Drugs drug) const
  {
    return current_drugs->find(drug) != current_drugs->end();
  }

  bool reallyLucky() const
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, m_odds);

    unsigned int draw1 = dist(gen);
    unsigned int draw2 = dist(gen);

    std::cout << "\t[DEBUG] Ressurrection Odds: 1/" << m_odds << std::endl;
    std::cout << "\t        Testing " << draw1 << " == " << draw2 << std::endl;

    return dist(gen) == dist(gen);
  }
};

#endif
