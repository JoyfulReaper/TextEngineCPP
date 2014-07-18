/*
 * TextEngine: serialization_adaptors.hpp
 * Copyright (C) 2014 Kyle Givler
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file serialization_adaptors.hpp
 * @author Kyle Givler
 */

#ifndef _SERIALIZATION_ADAPTORS_H_
#define _SERIALIZATION_ADAPTORS_H_

#include <boost/filesystem/path.hpp>

namespace boost {
  namespace serialization {
    
    // std::unique_ptr
    template <class Archive, class T>
    inline void save(
      Archive & ar,
      const std::unique_ptr<T> &t,
      const unsigned int file_version)
    {
      const T *const tx = t.get();
      ar << tx;
    }
    
    template<class Archive, class T>
    inline void load(
      Archive & ar,
      std::unique_ptr<T> &t,
      const unsigned int file_version)
    {
      T *pTarget;
      ar >> pTarget;
      #if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1)
      t.release();
      t = std::unique_ptr<T>(pTarget);
      #else
      t.reset(pTarget);
      #endif
    }
    
    template<class Archive, class T>
    inline void serialize(
      Archive & ar, std::unique_ptr<T> &t,
      const unsigned int file_version)
    {
      boost::serialization::split_free(ar, t, file_version);
    }
    
    // boost::filesystem::path
    template <class Archive>
    inline void save(
      Archive & ar,
      const boost::filesystem::path &t,
      const unsigned int file_version)
    {
      const std::string tx = t.string();
      ar << tx;
    }
    
    template<class Archive>
    inline void load(
      Archive & ar,
      boost::filesystem::path &t,
      const unsigned int file_version)
    {
      std::string tx;
      ar >> tx;
      t = tx;
    }
    
    template<class Archive>
    inline void serialize(
      Archive & ar, boost::filesystem::path &t,
      const unsigned int file_version)
    {
      boost::serialization::split_free(ar, t, file_version);
    }
    
  } // boost
} // serialization
#endif