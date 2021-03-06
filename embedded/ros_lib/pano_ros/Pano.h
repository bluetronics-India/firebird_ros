#ifndef _ROS_pano_ros_Pano_h
#define _ROS_pano_ros_Pano_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "sensor_msgs/Image.h"

namespace pano_ros
{

  class Pano : public ros::Msg
  {
    public:
      std_msgs::Header header;
      const char* pano_id;
      float latitude;
      float longitude;
      float heading;
      const char* geo_tag;
      sensor_msgs::Image image;

    Pano():
      header(),
      pano_id(""),
      latitude(0),
      longitude(0),
      heading(0),
      geo_tag(""),
      image()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      uint32_t length_pano_id = strlen(this->pano_id);
      memcpy(outbuffer + offset, &length_pano_id, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->pano_id, length_pano_id);
      offset += length_pano_id;
      offset += serializeAvrFloat64(outbuffer + offset, this->latitude);
      offset += serializeAvrFloat64(outbuffer + offset, this->longitude);
      offset += serializeAvrFloat64(outbuffer + offset, this->heading);
      uint32_t length_geo_tag = strlen(this->geo_tag);
      memcpy(outbuffer + offset, &length_geo_tag, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->geo_tag, length_geo_tag);
      offset += length_geo_tag;
      offset += this->image.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t length_pano_id;
      memcpy(&length_pano_id, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_pano_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_pano_id-1]=0;
      this->pano_id = (char *)(inbuffer + offset-1);
      offset += length_pano_id;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->latitude));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->longitude));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->heading));
      uint32_t length_geo_tag;
      memcpy(&length_geo_tag, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_geo_tag; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_geo_tag-1]=0;
      this->geo_tag = (char *)(inbuffer + offset-1);
      offset += length_geo_tag;
      offset += this->image.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "pano_ros/Pano"; };
    const char * getMD5(){ return "aedf66295b374a7249a786af27aecc87"; };

  };

}
#endif