#ifndef _PATH_HPP_
#define _PATH_HPP_

#include <agg_basics.h>
#include <agg_trans_affine.h>

class SimplePath
{
  public:
    SimplePath(const float *points, int size, bool close) : m_points(points), m_size(size), m_pos(0), m_close(close)
    {
    }

    void rewind(int path = 0)
    {
        m_pos = 0;
    }

    unsigned vertex(double *x, double *y)
    {
        if (m_pos < m_size)
        {
            *x = m_points[m_pos++];
            *y = m_points[m_pos++];
            return (m_pos == 2 ? agg::path_cmd_move_to : agg::path_cmd_line_to);
        }
        else if (m_close && m_pos == m_size)
        {
            m_pos += 2;
            *x = m_points[0];
            *y = m_points[1];
            return agg::path_cmd_line_to;
        }
        else if (m_close && m_pos == m_size + 2)
        {
            m_pos += 2;
            *x = m_points[2];
            *y = m_points[3];
            return agg::path_cmd_line_to;
        }
        return agg::path_cmd_stop;
    }

  private:
    const float *m_points;
    int m_size;
    int m_pos;
    bool m_close;
};

struct CmdVertex
{
    agg::path_commands_e cmd;
    double x;
    double y;
};
#endif //_PATH_HPP_
