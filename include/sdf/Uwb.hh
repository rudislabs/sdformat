/*
 * Copyright 2023 Open Source Robotics Foundation
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
#ifndef SDF_UWB_HH_
#define SDF_UWB_HH_

#include <gz/utils/ImplPtr.hh>

#include <sdf/Error.hh>
#include <sdf/Element.hh>
#include <sdf/sdf_config.h>

namespace sdf
{
  // Inline bracket to help doxygen filtering.
  inline namespace SDF_VERSION_NAMESPACE {
  /// \brief Uwb contains information about a general
  /// purpose Uwb sensor.
  /// This sensor can be attached to a link.
  class SDFORMAT_VISIBLE Uwb
  {
    /// \brief Default constructor
    public: Uwb();

    /// \brief Load the Uwb based on an element pointer.
    /// This is *not* the usual entry point. Typical usage of the SDF DOM is
    /// through the Root object.
    /// \param[in] _sdf The SDF Element pointer
    /// \return Errors, which is a vector of Error objects. Each Error includes
    /// an error code and message. An empty vector indicates no error.
    public: Errors Load(ElementPtr _sdf);

    /// \brief Get a pointer to the SDF element that was used during
    /// load.
    /// \return SDF element pointer. The value will be nullptr if Load has
    /// not been called.
    public: sdf::ElementPtr Element() const;

    /// \brief Return true if both Uwb objects contain the
    /// same values.
    /// \param[_in] _uwb Uwb value to compare.
    /// \return True if 'this' == _uwb.
    public: bool operator==(const Uwb &_uwb) const;

    /// \brief Return true this Uwb object does not contain
    /// the same values as the passed in parameter.
    /// \param[_in] _uwb Uwb value to compare.
    /// \return True if 'this' != _uwb.
    public: bool operator!=(const Uwb &_uwb) const;

    /// \brief This string represents special hardcoded use cases that are
    /// commonly seen with drones:
    ///   - NED: The Uwb sensor XYZ aligns with NED, where NED orientation relative
    ///          to the world is defined by the SphericalCoordinates class.
    ///   - ENU: The Uwb sensor XYZ aligns with ENU, where ENU orientation relative
    ///          to the world is defined by the SphericalCoordinates class.
    ///   - NWU: The Uwb sensor XYZ aligns with NWU, where NWU orientation relative
    ///          to the world is defined by the SphericalCoordinates class.
    /// \return Localization frame name
    public: const std::string &Localization() const;

    /// \brief See Localization(const std::string &).
    /// \param[in] _localization Localization frame name
    public: void SetLocalization(const std::string &_localization);

        /// \brief Get whether orientation data generation is enabled.
    /// \return True if orientation data generation is enabled orientation data,
    /// false otherwise.
    public: bool OrientationEnabled() const;

    /// \brief Set whether to enable orientation data generation.
    /// \param[in] _enabled True to enabled orientation data, false to disable
    /// it.
    public: void SetOrientationEnabled(bool _enabled);
    
    /// \brief Create and return an SDF element filled with data from this
    /// uwb sensor.
    /// Note that parameter passing functionality is not captured with this
    /// function.
    /// \return SDF element pointer with updated sensor values.
    public: sdf::ElementPtr ToElement() const;

    /// \brief Private data pointer.
    GZ_UTILS_IMPL_PTR(dataPtr)
  };
  }
}
#endif
