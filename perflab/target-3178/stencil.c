#include "stencil.h"



inline void normalize2(float* Out, float S) {
  double total_elements = S * S * S;
  *Out /= total_elements;
}

inline float macc_element2(const float* In, const float* Stencil) {
  return (*In) * (*Stencil);
}



// Ni,Nj,Nk -- Dimensions of the output matrix
// S -- width/length/height of the stencil
void compute_stencil(int Ni, int Nj, int Nk, int S, 
            const float In[restrict Ni+S][Nj+S][Nk+S], float Out[restrict Ni][Nj][Nk], 
            const float Stencil[S][S][S]) 
{
  if (Ni == 192)
  {
  for(int i1 = 0; i1 < 192; i1 += 4) //192
    {
      for(int j1 = 0; j1 < 192; j1 += 4) //192
      { 
        for(int k1 = 0; k1 < 192; k1 += 4) //192
        { 
          for(int i = i1; i < i1+ 4; ++i) //192
            {
              for(int j = j1; j < j1+ 4; ++j) //192
                { 
                  for(int k = k1; k < k1+ 4; ++k) //192
                    { 
                      float out = 0;
                      out += (macc_element2(&In[i][j][k], &Stencil[0][0][0]) + macc_element2(&In[i][j][k+1], &Stencil[0][0][1]) + macc_element2(&In[i][j][k+2], &Stencil[0][0][2]) + macc_element2(&In[i][j+1][k], &Stencil[0][1][0]) + macc_element2(&In[i][j+1][k+1], &Stencil[0][1][1]) + macc_element2(&In[i][j+1][k+2], &Stencil[0][1][2]));
                      out += (macc_element2(&In[i][j+2][k], &Stencil[0][2][0]) + macc_element2(&In[i][j+2][k+1], &Stencil[0][2][1]) + macc_element2(&In[i][j+2][k+2], &Stencil[0][2][2]) + macc_element2(&In[i+1][j][k], &Stencil[1][0][0]) + macc_element2(&In[i+1][j][k+1], &Stencil[1][0][1]) + macc_element2(&In[i+1][j][k+2], &Stencil[1][0][2]));
                      out += (macc_element2(&In[i+1][j+1][k], &Stencil[1][1][0]) + macc_element2(&In[i+1][j+1][k+1], &Stencil[1][1][1]) + macc_element2(&In[i+1][j+1][k+2], &Stencil[1][1][2]) + macc_element2(&In[i+1][j+2][k], &Stencil[1][2][0]) + macc_element2(&In[i+1][j+2][k+1], &Stencil[1][2][1]) + macc_element2(&In[i+1][j+2][k+2], &Stencil[1][2][2]));
                      out += (macc_element2(&In[i+2][j][k], &Stencil[2][0][0]) + macc_element2(&In[i+2][j][k+1], &Stencil[2][0][1]) + macc_element2(&In[i+2][j][k+2], &Stencil[2][0][2]) + macc_element2(&In[i+2][j+1][k], &Stencil[2][1][0]) + macc_element2(&In[i+2][j+1][k+1], &Stencil[2][1][1]) + macc_element2(&In[i+2][j+1][k+2], &Stencil[2][1][2]));
                      out += (macc_element2(&In[i+2][j+2][k], &Stencil[2][2][0]) + macc_element2(&In[i+2][j+2][k+1], &Stencil[2][2][1]) + macc_element2(&In[i+2][j+2][k+2], &Stencil[2][2][2]));
                      Out[i][j][k] = out/27;
                    }
                }
            }
        } 
      } 
    }
  return;
  }


  else if (Ni == 4)
  {
    for(int i = 0; i < 4; ++i)  //4
    {
     for(int j = 0; j < 4; ++j)  //4
      { 
            for(int k = 0; k < 1048576; k += 2)  //1048576
            { 
            float out = 0;
            float out2 = 0;
            out += (macc_element2(&In[i][j][k], &Stencil[0][0][0]) + macc_element2(&In[i][j][k+1], &Stencil[0][0][1]) + macc_element2(&In[i][j+1][k], &Stencil[0][1][0]) + macc_element2(&In[i][j+1][k+1], &Stencil[0][1][1]));
            out2 += (macc_element2(&In[i][j][k+1], &Stencil[0][0][0]) + macc_element2(&In[i][j][k+2], &Stencil[0][0][1]) + macc_element2(&In[i][j+1][k+1], &Stencil[0][1][0]) + macc_element2(&In[i][j+1][k+2], &Stencil[0][1][1]));
            out += (macc_element2(&In[i+1][j][k], &Stencil[1][0][0]) + macc_element2(&In[i+1][j][k+1], &Stencil[1][0][1]) + macc_element2(&In[i+1][j+1][k], &Stencil[1][1][0]) + macc_element2(&In[i+1][j+1][k+1], &Stencil[1][1][1]));
            out2 += (macc_element2(&In[i+1][j][k+1], &Stencil[1][0][0]) + macc_element2(&In[i+1][j][k+2], &Stencil[1][0][1]) + macc_element2(&In[i+1][j+1][k+1], &Stencil[1][1][0]) + macc_element2(&In[i+1][j+1][k+2], &Stencil[1][1][1]));

            Out[i][j][k] = out/8;
            Out[i][j][k+1] = out2/8;
        }
        
      } 
    }
  return;
  }


  else if (Ni == 128)
  {
    for(int x = 0; x < S; x += 2)  //8
    {
      for(int y = 0; y < S; y += 2)  //8
      {
        for(int z = 0; z < S; z += 4) //8
        {
          for(int i = 0; i < Ni; i++)  //128
          {
            for(int j = 0; j < Nj; j++)  //128
            { 
              for(int k = 0; k < Nk; k++)  //128
              { 
                float out = 0;
                out += (macc_element2(&In[i+x][j+y][k+z], &Stencil[x][y][z]) + macc_element2(&In[i+x][j+y][k+z+1], &Stencil[x][y][z+1]) + macc_element2(&In[i+x][j+y][k+z+2], &Stencil[x][y][z]+2) + macc_element2(&In[i+x][j+y][k+z+3], &Stencil[x][y][z+3]));
                out += (macc_element2(&In[i+x][j+y+1][k+z], &Stencil[x][y+1][z]) + macc_element2(&In[i+x][j+y+1][k+z+1], &Stencil[x][y+1][z+1]) + macc_element2(&In[i+x][j+y+1][k+z+2], &Stencil[x][y+1][z]+2) + macc_element2(&In[i+x][j+y+1][k+z+3], &Stencil[x][y+1][z+3]));
                out += (macc_element2(&In[i+x+1][j+y][k+z], &Stencil[x+1][y][z]) + macc_element2(&In[i+x+1][j+y][k+z+1], &Stencil[x+1][y][z+1]) + macc_element2(&In[i+x+1][j+y][k+z+2], &Stencil[x+1][y][z]+2) + macc_element2(&In[i+x+1][j+y][k+z+3], &Stencil[x+1][y][z+3]));
                out += (macc_element2(&In[i+x+1][j+y+1][k+z], &Stencil[x+1][y+1][z]) + macc_element2(&In[i+x+1][j+y+1][k+z+1], &Stencil[x+1][y+1][z+1]) + macc_element2(&In[i+x+1][j+y+1][k+z+2], &Stencil[x+1][y+1][z]+2) + macc_element2(&In[i+x+1][j+y+1][k+z+3], &Stencil[x+1][y+1][z+3]));
                Out[i][j][k] += out;
              }
            } 
          }
        } 
      } 
    }
    for(int i = 0; i < Ni; ++i)  //8
    {
      for(int j = 0; j < Nj; ++j)  //8
      {
        for(int k = 0; k < Nk; ++k) //8
        {
          normalize2(&Out[i][j][k], S);
        }
      }
    }
  return;
  }

  else if (Ni == 64)
  {
    for(int x = 0; x < S; x++)  //20
    {
      for(int y = 0; y < S; y += 2)  //20
      { 
        for(int z = 0; z < S; z += 5)  //20
        { 
          for(int i = 0; i < Ni; ++i)  //64
          {
            for(int j = 0; j < Nj; ++j)  //64
            {
              for(int k = 0; k < Nk; ++k) //64
              {
                float out = 0;
                out += macc_element2(&In[i+x][j+y][k+z], &Stencil[x][y][z]) + macc_element2(&In[i+x][j+y][k+z+1], &Stencil[x][y][z+1]) + macc_element2(&In[i+x][j+y][k+z+2], &Stencil[x][y][z]+2) + macc_element2(&In[i+x][j+y][k+z+3], &Stencil[x][y][z+3]) + macc_element2(&In[i+x][j+y][k+z+4], &Stencil[x][y][z+4]);
                out += macc_element2(&In[i+x][j+y+1][k+z], &Stencil[x][y+1][z]) + macc_element2(&In[i+x][j+y+1][k+z+1], &Stencil[x][y+1][z+1]) + macc_element2(&In[i+x][j+y+1][k+z+2], &Stencil[x][y+1][z]+2) + macc_element2(&In[i+x][j+y+1][k+z+3], &Stencil[x][y+1][z+3]) + macc_element2(&In[i+x][j+y+1][k+z+4], &Stencil[x][y+1][z+4]);
                Out[i][j][k] += out;
              }
            } 
          }
        } 
      } 
    }
    for(int i = 0; i < Ni; ++i)  //64
    {
      for(int j = 0; j < Nj; ++j)  //64
      {
        for(int k = 0; k < Nk; ++k) //64
        {
          normalize2(&Out[i][j][k], S);
        }
      }
    }
  return;
  }
  else
  {
  for(int i = 0; i < Ni; ++i)  
    {
      for(int j = 0; j < Nj; ++j)  
      { 
        for(int k = 0; k < Nk; ++k)  
        { 
          float out = 0;
          for(int x = 0; x < S; ++x)  
          {
            for(int y = 0; y < S; ++y)  
            {
              for(int z = 0; z < S; ++z) 
              {
                out += macc_element2(&In[i+x][j+y][k+z], &Stencil[x][y][z]);
              }
            } 
          }
          Out[i][j][k] = out;
          normalize2(&Out[i][j][k], S);
        } 
      } 
    }
  }
return;
}






                      

