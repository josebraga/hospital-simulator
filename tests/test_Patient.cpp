#include <gtest/gtest.h>
#include "../src/patient.h"

/******************************************************************************
 * No drugs administered to patient with Condition initial_cond
 ******************************************************************************/
Condition AdminAndTest(Condition initial_cond)
{
  Patient subject {initial_cond};
  std::set<Drugs> drugs;
  subject.takes(drugs);
  return subject.getState();
}

/******************************************************************************
 * One drug administered to patient with Condition initial_cond
 ******************************************************************************/
Condition AdminAndTest(Condition initial_cond, Drugs drug)
{
  Patient subject {initial_cond};

  std::set<Drugs> drugs;
  drugs.insert(drug);

  subject.takes(drugs);

  return subject.getState();
}

/******************************************************************************
 * Two drugs administered to patient with Condition initial_cond
 ******************************************************************************/
Condition AdminAndTest(Condition initial_cond, Drugs drug1, Drugs drug2)
{
  Patient subject {initial_cond};

  std::set<Drugs> drugs;
  drugs.insert(drug1);
  drugs.insert(drug2);

  subject.takes(drugs);

  return subject.getState();
}

/**************************
 * From Healthy transitions
 **************************/
TEST(testHealthyToFeverWithInsulinAndAntibiotic, integerTests)
{
  EXPECT_EQ(Condition::FEVER, AdminAndTest(Condition::HEALTHY, Drugs::INSULIN, Drugs::ANTIBIOTIC));
}

TEST(testHealthyToHealthy, integerTests)
{
  // insufficient to change condition
  EXPECT_EQ(Condition::HEALTHY, AdminAndTest(Condition::HEALTHY));
  EXPECT_EQ(Condition::HEALTHY, AdminAndTest(Condition::HEALTHY, Drugs::INSULIN));
  EXPECT_EQ(Condition::HEALTHY, AdminAndTest(Condition::HEALTHY, Drugs::ANTIBIOTIC));
  EXPECT_EQ(Condition::HEALTHY, AdminAndTest(Condition::HEALTHY, Drugs::PARACETAMOL));
}

/**************************
 * From Fever transitions
 **************************/
TEST(testFeverToHealthyWithAspirin, integerTests)
{
  EXPECT_EQ(Condition::HEALTHY, AdminAndTest(Condition::FEVER, Drugs::ASPIRIN));
}

TEST(testFeverToHealthyWithParacetamol, integerTests)
{
  EXPECT_EQ(Condition::HEALTHY, AdminAndTest(Condition::FEVER, Drugs::PARACETAMOL));
}

TEST(testFeverToFever, integerTests)
{
  // insufficient to change condition
  EXPECT_EQ(Condition::FEVER, AdminAndTest(Condition::FEVER));
  EXPECT_EQ(Condition::FEVER, AdminAndTest(Condition::FEVER, Drugs::ANTIBIOTIC));
  EXPECT_EQ(Condition::FEVER, AdminAndTest(Condition::FEVER, Drugs::INSULIN));
}

/**************************
 * From Diabetes
 **************************/
TEST(testDiabetesToDiabetesWithInsulin, integerTests)
{
  EXPECT_EQ(Condition::DIABETES, AdminAndTest(Condition::DIABETES, Drugs::INSULIN));
}

TEST(testDiabetesToDeadWithoutInsulin, integerTests)
{
  EXPECT_EQ(Condition::DEAD, AdminAndTest(Condition::DIABETES));
  EXPECT_EQ(Condition::DEAD, AdminAndTest(Condition::DIABETES, Drugs::ASPIRIN));
  EXPECT_EQ(Condition::DEAD, AdminAndTest(Condition::DIABETES, Drugs::ANTIBIOTIC));
  EXPECT_EQ(Condition::DEAD, AdminAndTest(Condition::DIABETES, Drugs::PARACETAMOL));
}

/**************************
 * From Tuberculosis
 **************************/
TEST(testTuberculosisToHealthyWithAntibiotic, integerTests)
{
  EXPECT_EQ(Condition::HEALTHY, AdminAndTest(Condition::TUBERCULOSIS, Drugs::ANTIBIOTIC));
}

TEST(testTuberculosisToTuberculosis, integerTests)
{
  // insufficient to change condition
  EXPECT_EQ(Condition::TUBERCULOSIS, AdminAndTest(Condition::TUBERCULOSIS));
  EXPECT_EQ(Condition::TUBERCULOSIS, AdminAndTest(Condition::TUBERCULOSIS, Drugs::ASPIRIN));
  EXPECT_EQ(Condition::TUBERCULOSIS, AdminAndTest(Condition::TUBERCULOSIS, Drugs::INSULIN));
  EXPECT_EQ(Condition::TUBERCULOSIS, AdminAndTest(Condition::TUBERCULOSIS, Drugs::PARACETAMOL));
}

/**************************
 * Dead combo
 **************************/
TEST(testDeathWithParacetamolAndAspirin, integerTests)
{
  EXPECT_EQ(Condition::DEAD, AdminAndTest(Condition::HEALTHY, Drugs::PARACETAMOL, Drugs::ASPIRIN));
  EXPECT_EQ(Condition::DEAD, AdminAndTest(Condition::FEVER, Drugs::PARACETAMOL, Drugs::ASPIRIN));
  EXPECT_EQ(Condition::DEAD, AdminAndTest(Condition::DIABETES, Drugs::PARACETAMOL, Drugs::ASPIRIN));
  EXPECT_EQ(Condition::DEAD, AdminAndTest(Condition::TUBERCULOSIS, Drugs::PARACETAMOL, Drugs::ASPIRIN));
}

/**************************
 * Main Test Loop
 **************************/
int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
