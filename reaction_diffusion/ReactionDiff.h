#ifndef REACTIONDIFF_H
#define REACTIONDIFF_H

#define MAX 200

class ReactionDiff
{
  int TYPE; // 1 -> stripes, 2 -> spots
  int xsize,ysize;
  float p1,p2,p3;
  float diff1, diff2;
  float arand;
  float speed;

  float a[MAX][MAX];
  float b[MAX][MAX];
  float c[MAX][MAX];
  float d[MAX][MAX];
  float e[MAX][MAX];
  float ai[MAX][MAX];
  float da[MAX][MAX];
  float db[MAX][MAX];
  float dc[MAX][MAX];
  float dd[MAX][MAX];
  float de[MAX][MAX];

  float min,max;

  public:
    ReactionDiff();
    void init(int,float);
    void set_size(int, int);
    void set_p(float, float, float);
    void set_diff(float, float);
    void set_arand(float);
    float frand(float, float);
    void run_stripe(void);
    void update_min_max(float[MAX][MAX]);
    void calculate_semistable(void);
    void run(void);
    float get(int,int);
    float get_min(void);
    float get_max(void);
};

#endif
