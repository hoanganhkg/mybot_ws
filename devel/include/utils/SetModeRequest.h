// Generated by gencpp from file utils/SetModeRequest.msg
// DO NOT EDIT!


#ifndef UTILS_MESSAGE_SETMODEREQUEST_H
#define UTILS_MESSAGE_SETMODEREQUEST_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace utils
{
template <class ContainerAllocator>
struct SetModeRequest_
{
  typedef SetModeRequest_<ContainerAllocator> Type;

  SetModeRequest_()
    : base_mode(0)
    , custom_mode()  {
    }
  SetModeRequest_(const ContainerAllocator& _alloc)
    : base_mode(0)
    , custom_mode(_alloc)  {
  (void)_alloc;
    }



   typedef uint8_t _base_mode_type;
  _base_mode_type base_mode;

   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _custom_mode_type;
  _custom_mode_type custom_mode;



// reducing the odds to have name collisions with Windows.h 
#if defined(_WIN32) && defined(MAV_MODE_PREFLIGHT)
  #undef MAV_MODE_PREFLIGHT
#endif
#if defined(_WIN32) && defined(MAV_MODE_STABILIZE_DISARMED)
  #undef MAV_MODE_STABILIZE_DISARMED
#endif
#if defined(_WIN32) && defined(MAV_MODE_STABILIZE_ARMED)
  #undef MAV_MODE_STABILIZE_ARMED
#endif
#if defined(_WIN32) && defined(MAV_MODE_MANUAL_DISARMED)
  #undef MAV_MODE_MANUAL_DISARMED
#endif
#if defined(_WIN32) && defined(MAV_MODE_MANUAL_ARMED)
  #undef MAV_MODE_MANUAL_ARMED
#endif
#if defined(_WIN32) && defined(MAV_MODE_GUIDED_DISARMED)
  #undef MAV_MODE_GUIDED_DISARMED
#endif
#if defined(_WIN32) && defined(MAV_MODE_GUIDED_ARMED)
  #undef MAV_MODE_GUIDED_ARMED
#endif
#if defined(_WIN32) && defined(MAV_MODE_AUTO_DISARMED)
  #undef MAV_MODE_AUTO_DISARMED
#endif
#if defined(_WIN32) && defined(MAV_MODE_AUTO_ARMED)
  #undef MAV_MODE_AUTO_ARMED
#endif
#if defined(_WIN32) && defined(MAV_MODE_TEST_DISARMED)
  #undef MAV_MODE_TEST_DISARMED
#endif
#if defined(_WIN32) && defined(MAV_MODE_TEST_ARMED)
  #undef MAV_MODE_TEST_ARMED
#endif

  enum {
    MAV_MODE_PREFLIGHT = 0u,
    MAV_MODE_STABILIZE_DISARMED = 80u,
    MAV_MODE_STABILIZE_ARMED = 208u,
    MAV_MODE_MANUAL_DISARMED = 64u,
    MAV_MODE_MANUAL_ARMED = 192u,
    MAV_MODE_GUIDED_DISARMED = 88u,
    MAV_MODE_GUIDED_ARMED = 216u,
    MAV_MODE_AUTO_DISARMED = 92u,
    MAV_MODE_AUTO_ARMED = 220u,
    MAV_MODE_TEST_DISARMED = 66u,
    MAV_MODE_TEST_ARMED = 194u,
  };


  typedef boost::shared_ptr< ::utils::SetModeRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::utils::SetModeRequest_<ContainerAllocator> const> ConstPtr;

}; // struct SetModeRequest_

typedef ::utils::SetModeRequest_<std::allocator<void> > SetModeRequest;

typedef boost::shared_ptr< ::utils::SetModeRequest > SetModeRequestPtr;
typedef boost::shared_ptr< ::utils::SetModeRequest const> SetModeRequestConstPtr;

// constants requiring out of line definition

   

   

   

   

   

   

   

   

   

   

   



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::utils::SetModeRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::utils::SetModeRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::utils::SetModeRequest_<ContainerAllocator1> & lhs, const ::utils::SetModeRequest_<ContainerAllocator2> & rhs)
{
  return lhs.base_mode == rhs.base_mode &&
    lhs.custom_mode == rhs.custom_mode;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::utils::SetModeRequest_<ContainerAllocator1> & lhs, const ::utils::SetModeRequest_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace utils

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::utils::SetModeRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::utils::SetModeRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::utils::SetModeRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::utils::SetModeRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::utils::SetModeRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::utils::SetModeRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::utils::SetModeRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d770431847cad3a8f50a81ec70ddf0e2";
  }

  static const char* value(const ::utils::SetModeRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd770431847cad3a8ULL;
  static const uint64_t static_value2 = 0xf50a81ec70ddf0e2ULL;
};

template<class ContainerAllocator>
struct DataType< ::utils::SetModeRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "utils/SetModeRequest";
  }

  static const char* value(const ::utils::SetModeRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::utils::SetModeRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# set FCU mode\n"
"#\n"
"# Known custom modes listed here:\n"
"# http://wiki.ros.org/mavros/CustomModes\n"
"\n"
"# basic modes from MAV_MODE\n"
"uint8 MAV_MODE_PREFLIGHT		= 0\n"
"uint8 MAV_MODE_STABILIZE_DISARMED	= 80\n"
"uint8 MAV_MODE_STABILIZE_ARMED		= 208\n"
"uint8 MAV_MODE_MANUAL_DISARMED		= 64\n"
"uint8 MAV_MODE_MANUAL_ARMED		= 192\n"
"uint8 MAV_MODE_GUIDED_DISARMED		= 88\n"
"uint8 MAV_MODE_GUIDED_ARMED		= 216\n"
"uint8 MAV_MODE_AUTO_DISARMED		= 92\n"
"uint8 MAV_MODE_AUTO_ARMED		= 220\n"
"uint8 MAV_MODE_TEST_DISARMED		= 66\n"
"uint8 MAV_MODE_TEST_ARMED		= 194\n"
"\n"
"uint8 base_mode		# filled by MAV_MODE enum value or 0 if custom_mode != ''\n"
"string custom_mode	# string mode representation or integer\n"
;
  }

  static const char* value(const ::utils::SetModeRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::utils::SetModeRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.base_mode);
      stream.next(m.custom_mode);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SetModeRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::utils::SetModeRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::utils::SetModeRequest_<ContainerAllocator>& v)
  {
    s << indent << "base_mode: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.base_mode);
    s << indent << "custom_mode: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.custom_mode);
  }
};

} // namespace message_operations
} // namespace ros

#endif // UTILS_MESSAGE_SETMODEREQUEST_H
