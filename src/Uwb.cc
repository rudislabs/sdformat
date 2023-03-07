/*
 * Copyright 2019 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <array>
#include <string>
#include "sdf/Uwb.hh"
#include "sdf/parser.hh"

using namespace sdf;

/// \brief Private uwb data.
class sdf::Uwb::Implementation
{
  /// \brief Localization string
  public: std::string localization = "NED";

  /// \brief The SDF element pointer used during load.
  public: sdf::ElementPtr sdf;

  /// \brief True to enable orientation
  public: bool orientationEnabled = true;
};

//////////////////////////////////////////////////
Uwb::Uwb()
  : dataPtr(gz::utils::MakeImpl<Implementation>())
{
}

//////////////////////////////////////////////////
Errors Uwb::Load(ElementPtr _sdf)
{
  Errors errors;

  this->dataPtr->sdf = _sdf;

  // Check that the provided SDF element is a <uwb> element.
  // This is an error that cannot be recovered, so return an error.
  if (_sdf->GetName() != "uwb")
  {
    errors.push_back({ErrorCode::ELEMENT_INCORRECT_TYPE,
        "Attempting to load an UWB, but the provided SDF element is "
        "not an <uwb>."});
    return errors;
  }

  if (_sdf->HasElement("orientation_reference_frame"))
  {
    sdf::ElementPtr elem = _sdf->GetElement("orientation_reference_frame");
    this->dataPtr->localization = elem->Get<std::string>("localization",
        this->dataPtr->localization).first;
  }

  if (_sdf->HasElement("enable_orientation"))
  {
    this->dataPtr->orientationEnabled = _sdf->Get<bool>(
        "enable_orientation", this->dataPtr->orientationEnabled).first;
  }

  return errors;
}

//////////////////////////////////////////////////
sdf::ElementPtr Uwb::Element() const
{
  return this->dataPtr->sdf;
}

//////////////////////////////////////////////////
bool Uwb::operator!=(const Uwb &_uwb) const
{
  return !(*this == _uwb);
}

//////////////////////////////////////////////////
bool Uwb::operator==(const Uwb &_uwb) const
{
  return this->dataPtr->localization == _uwb.dataPtr->localization;
}

//////////////////////////////////////////////////
const std::string &Uwb::Localization() const
{
  return this->dataPtr->localization;
}

//////////////////////////////////////////////////
void Uwb::SetLocalization(const std::string &_localization)
{
  this->dataPtr->localization = _localization;
}

//////////////////////////////////////////////////
void Uwb::SetOrientationEnabled(bool _enabled)
{
  this->dataPtr->orientationEnabled = _enabled;
}

//////////////////////////////////////////////////
bool Uwb::OrientationEnabled() const
{
  return this->dataPtr->orientationEnabled;
}

/////////////////////////////////////////////////
sdf::ElementPtr Uwb::ToElement() const
{
  sdf::ElementPtr elem(new sdf::Element);
  sdf::initFile("uwb.sdf", elem);

  sdf::ElementPtr orientationRefFrameElem =
    elem->GetElement("orientation_reference_frame");
  orientationRefFrameElem->GetElement("localization")->Set<std::string>(
      this->Localization());

  elem->GetElement("enable_orientation")->Set<bool>(
      this->OrientationEnabled());

  return elem;
}
