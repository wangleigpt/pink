#ifndef PINK_REDIS_CONN_H_
#define PINK_REDIS_CONN_H_

#include "status.h"
#include "csapp.h"
#include "pink_define.h"
#include "pink_util.h"
#include "pink_conn.h"
#include "xdebug.h"
#include <map>
#include <vector>

namespace pink {

typedef std::vector<std::string> RedisCmdArgsType;
class RedisConn: public PinkConn
{
public:
  RedisConn(const int fd, const std::string &ip_port);
  virtual ~RedisConn();
  void ResetClient();

  virtual ReadStatus GetRequest();
  virtual WriteStatus SendReply();

  virtual int DealMessage() = 0;

  ConnStatus connStatus_;

private:
  
  int32_t last_read_pos_;
  int32_t next_parse_pos_;
  int32_t req_type_;
  int32_t multibulk_len_;
  int32_t bulk_len_;
  bool is_find_sep_;
  bool is_overtake_;

  /*
   * The Variable need by read the buf,
   * We allocate the memory when we start the server
   */
  char* rbuf_;
  uint32_t wbuf_pos_;

  ReadStatus ProcessInputBuffer();
  ReadStatus ProcessMultibulkBuffer();
  ReadStatus ProcessInlineBuffer();
  int32_t FindNextSeparators();
  int32_t GetNextNum(int32_t pos, int32_t *value);

protected:
  char* wbuf_;
  uint32_t wbuf_len_;
  RedisCmdArgsType argv_;

};
}

#endif
