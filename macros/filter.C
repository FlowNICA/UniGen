/**
 * UniGen - Common Format for Event Generators in High-energy and Nuclear
 * Physics Copyright (C) 2006 - 2019 GSI Helmholtzzentrum fuer
 * Schwerionenforschung GmbH
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

{
  // Create libraries
  gSystem->Load("libUniGen");
  gSystem->Load("libTasks");

  // Create manager
  UManager *mgr = new UManager();

  // Set in/out file names
  mgr->SetInputFile((TString(getenv("UNIGEN")) + "/data/urqmd/ug.root").Data());
  mgr->SetOutputFile("urqmd_filtered.root");

  // Create filter task
  UTaskFilter *task = new UTaskFilter("filter");
  task->AddParticle(211);
  task->AddParticle(-211);
  task->SetFilterMode(1);
  mgr->AddTask(task);

  // Initialisation
  mgr->Init();

  // Run
  mgr->Run();
}
