/*
* Copyright (C) 2010 Javeline BV
*
* This library is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License as published by the Free Software
* Foundation; either version 2 of the License, or (at your option) any later
* version.
*
* This library is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
* details.
*
* You should have received a copy of the GNU General Public License along with
* this library; if not, write to the Free Software Foundation, Inc., 51
* Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/
#ifndef O3_C_IMAGE1_H
#define O3_C_IMAGE1_H

#include <lib_zlib.h>
#include <core/o3_math.h>
#include <math.h>

#include <lib_png.h>

namespace o3 {

    const double curve_distance_epsilon                  = 1e-30;
    const double curve_collinearity_epsilon              = 1e-30;
    const double curve_angle_tolerance_epsilon           = 0.01;


	//..include agg
	
	


	struct cImage1 : cScr {
		o3_begin_class(cScr)
			o3_end_class()

#include "o3_cImage1_scr.h"

		enum Modes
		{
			MODE_GRAY,
			MODE_BW,
			MODE_ARGB,
			MODE_RGB,
			__MODE_COUNT
		};
		
		enum FullStyles
		{
			FILL_SOLID,
			FILL_BLEND,
			__FILLSTYLE_COUNT
		};

		Str m_mode;
		int m_mode_int;
		
		class Path 
		{
		public:
			tVec<V2<float> > m_path;
		};
		
		tVec<Path> m_paths;
		V2<float> m_lastpoint;
		
		class RenderState
		{
		public:
			unsigned int FillColor;
			unsigned int StrokeColor;
			float StrokeWidth;

			int FillStyle;
			M33<float> Transformation;


			float miterLimit;
		};

		tVec<RenderState> m_renderstates;

		size_t m_w, m_h, m_stride;
		int    m_bytesperpixel;
		int    m_bitdepth;
		Buf	   m_mem;

		cImage1()
		{
			m_w = m_h = m_stride = 0;
			m_bitdepth = 32;
			m_bytesperpixel = 4;
			m_mode = Str("argb");
			SetupRenderState();
		};

		cImage1(size_t w, size_t h, const Str &mode)
		{
			m_w = w;
			m_h = h;
			m_stride = (m_w+7)&~(7);

			m_mode = mode;
			m_bytesperpixel = 4;
			m_bitdepth = 32;
			if (m_mode == "argb")
			{
				m_bytesperpixel = 4;
				m_bitdepth = 32;
				m_mode_int = MODE_ARGB;
			}
			else if (m_mode == "gray")
			{
				m_bitdepth = 8;
				m_bytesperpixel= 1;
				m_mode_int = MODE_GRAY;
			}
			else if (m_mode == "bw")
			{
				m_bitdepth = 1;
				m_bytesperpixel = 1;
				m_mode_int = MODE_BW;

			}
			else if (m_mode == "rgb")
			{
				m_bitdepth = 24;
				m_bytesperpixel = 3;
				m_mode_int = MODE_RGB;
			}

			SetupBuffer();
			SetupRenderState();
		};

		void SetupBuffer()
		{	
			size_t newsize = 0;
			switch(m_mode_int)
			{
			case MODE_BW:
				newsize = (m_stride * m_h)/8;
				break;
			default:
				newsize = m_stride * m_h * m_bytesperpixel;
				break;
			}
			m_mem.resize(newsize);
		};

		static o3_get o3_ext("cO3") siScr image(iCtx* ctx)
		{
			o3_trace3 trace;
			Var blob = ctx->value("image");

			if (blob.type() == Var::TYPE_VOID)
				blob = ctx->setValue("image", o3_new(cImage1)());
			return blob.toScr();
		}

		o3_fun siScr __self__()
		{
			o3_trace3 trace;

			return o3_new(cImage1)();
		}

		o3_fun siScr __self__(size_t w, size_t h, const Str &mode = Str("32") )
		{
			return o3_new(cImage1)(w,h,mode);
		}

		o3_get Str mode(){return m_mode;}

		o3_get size_t x(){return m_w;}
		o3_get size_t y(){return m_h;}

		o3_get size_t width(){return m_w;}
		o3_get size_t height(){return m_h;}
		
		unsigned char *getRowPtr(size_t y)
		{
			if (m_mode_int == MODE_BW) 
			{
				if (y< (int)m_h) 
				{
					return ((unsigned char *)m_mem.ptr() + (m_stride * y) / 8);
				};
			}
			else
			{
				if (y< m_h) 
				{
					return ((unsigned char *)m_mem.ptr() + (m_stride * y) * m_bytesperpixel);
				}
			};
			return 0;
		};
		
		o3_fun void clear(unsigned int color)
		{
			for (size_t y = 0;y<m_h;y++)
			{
				for (size_t x=0;x<m_w;x++) 
				{
					setPixel(x,y,color);
				};
			};
		};

		o3_fun void setPixel(size_t x, size_t y, unsigned int color)
		{
			unsigned char *D = getRowPtr(y);
			if(D)
			{
				if (x >= 0 && x < m_w)
				{
					switch(m_mode_int)
					{
						
					case MODE_BW:
						{
							int shift = x&7;
							x>>=3;
							int mask = 1<<shift;
							unsigned char *pixeldest = D + x;
							if (color&0xffffff)
							{
								*pixeldest |= mask;
							}
							else
							{
								*pixeldest &= ~mask;
							}
						};break;

					case MODE_ARGB:
						{
							unsigned int *pixeldest = ((unsigned int *)(D)) + x;
							
							unsigned char *srcchannels = (unsigned char *) &color;
							unsigned char a = srcchannels[3];
							if (a == 255)
							{
								*pixeldest = color;
							}
							else
							{
								unsigned char *dstchannels = (unsigned char *) pixeldest;
								unsigned char inva = ~a;
								srcchannels[3]= 0xff; //TODO dst alpha needs to get some meaning!
								for (int j= 0;j<3;j++)
								{
									srcchannels[j]= (dstchannels[j]*inva + srcchannels[j]*a)>>8;
								}
								//TODO: add blendpixel stuff that properly uses the alpha information.

								*pixeldest = color;
							};
						};break;
					};
				};
			};
		};

		o3_fun int getPixel(size_t x, size_t y)
		{
			unsigned char *D = getRowPtr(y);
			if(D)
			{
				if (x >= 0 && x < m_w)
				{
					switch (m_mode_int)
					{
					case MODE_BW:
						{
							int shift = x&7;
							x>>=3;
							int mask = 1<<shift;
							unsigned char *pixeldest = D + x;
							if (*pixeldest & mask) return 0xffffffff;
							return 0xff000000;
						};break;

					case MODE_ARGB:
						{
							unsigned int *pixeldest = ((unsigned int *)(D)) + x;
							return *pixeldest;
						};break;
					};
				};
			};
			return 0;
		};

		o3_fun int savePng(const Str &file_name, iEx **ex)
		{
			using namespace png;
			/* create file */
			if (m_w==0 ||m_h == 0)
			{
				cEx::fmt(ex,"[write_png_file] image must have both width and height >0 before something can be written!");			
				return 0;
			}

			png_structp png_ptr;
			png_infop info_ptr;

			FILE *fp = fopen(file_name, "wb");
			if (!fp){
				cEx::fmt(ex,"[write_png_file] File %s could not be opened for writing", file_name);			
				return 0;
			}

			/* initialize stuff */
			png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

			if (!png_ptr)
			{
				cEx::fmt(ex,"[write_png_file] png_create_write_struct failed");
				return 0;
			}

			info_ptr = png_create_info_struct(png_ptr);
			
			if (!info_ptr)
			{
				cEx::fmt(ex,"[write_png_file] png_create_info_struct failed");
				return 0; 
			}
			
			if (setjmp(png_jmpbuf(png_ptr)))
			{
				cEx::fmt(ex,"[write_png_file] Error during init_io");
				return 0;
			}

			png_init_io(png_ptr, fp);


			/* write header */
			if (setjmp(png_jmpbuf(png_ptr)))
			{
				cEx::fmt(ex,"[write_png_file] Error during writing header");
				return 0;
			};

			int color_type = 0;
			int bitdepth = 8;
		
			color_type = PNG_COLOR_TYPE_RGB_ALPHA;
			
			// TODO! add 1bit save
			
			png_set_IHDR(png_ptr, info_ptr, m_w, m_h,
				bitdepth, color_type, PNG_INTERLACE_NONE,
				PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

			png_write_info(png_ptr, info_ptr);

			if (setjmp(png_jmpbuf(png_ptr)))
			{
				cEx::fmt(ex,"[write_png_file] Error during writing bytes");
				return 0;
			};

			tVec<png_bytep> row_pointers(m_h);
			for (size_t y = 0;y<m_h;y++)
			{
				tVec <unsigned int> row(m_w);
				switch (m_mode_int)
				{
				case MODE_ARGB:
					{
						unsigned int *D = (unsigned int *)getRowPtr(y);
						for (size_t i =0 ;i<m_w;i++)
						{
							unsigned int const pixel = *D++;
							unsigned int shuffled = ((pixel >> 24)&0x255) + ((pixel << 8)&0xffffff00);
							row[i] = shuffled;

							unsigned char *c = (unsigned char*)&row[i];
							c[0] = (unsigned char)(pixel>>16);
							c[1] = (unsigned char)(pixel>>8);
							c[2] = (unsigned char)(pixel);
							c[3] = (unsigned char)(pixel>>24);
						}
					}break;
				case MODE_RGB:
					{
						unsigned char *D = (unsigned char *)getRowPtr(y);
						for (size_t i =0 ;i<m_w;i++)
						{
							unsigned char R = *D++;
							unsigned char G = *D++;
							unsigned char B = *D++;
							unsigned int const pixel = (R << 24) + (G << 16) + (B << 8) + 0xff ;
							row[i] = pixel;
						}
					}break;
				case MODE_BW:
					{
						unsigned char *D = (unsigned char *)getRowPtr(y);
						for (size_t i =0 ;i<m_w;i++)
						{
							int x = i>>3;
							int shift = i&7;
							if (*(D+x)&(1<<shift))
							{
								row[i] = 0xffffffff;
							}
							else
							{
								row[i] = 0xff000000;
							}							
						}
					}break;
				}
				png_write_row(png_ptr, (png_bytep)row.ptr());

			}

			//png_write_image(png_ptr, row_pointers.ptr());


			if (setjmp(png_jmpbuf(png_ptr)))
			{
				cEx::fmt(ex,"[write_png_file] Error during end of write");
				return 0;
			};

			png_write_end(png_ptr, NULL);

			/* cleanup heap allocation */
			
			fclose(fp);
			return 1;
		};
	

// png(bpp[1,8,24,32]) // return blob image.saveJpg(fsnode/filename, compression)
// jpg(compression) // return blob

// image = image.load(fsnode/filename); // autoformat image = image.loadJpg(fsnode/filename); image = image.loadPng(fsnode/filename);


	void Ensure32BitSurface()
	{
		// TODO -- with fallback
	};

	o3_fun void rect(int x, int y, int w, int h, unsigned int color)    // !ALLMODES!
	{
		for (int sy = y;sy<y+h;sy++)
		{
			for (int sx = x;sx<x+w;sx++)
			{
				setPixel(sx,sy,color);
			};
		};
	};

	o3_fun void line(int x0,int y0,int x1,int y1,unsigned int color)    // !ALLMODES!
	{
		bool steep = (abs(y1 - y0) > abs(x1 - x0));
		if (steep)
		{			 
			swap(x0, y0);
			swap(x1, y1);
		}
		if (x0 > x1)
		{
			swap(x0, x1);
			swap(y0, y1);
		}
		int deltax = x1 - x0;
		int deltay = abs(y1 - y0);
		int error = deltax / 2;
		int ystep;
		int y = y0;
		if (y0 < y1) 
		{
			ystep = 1;
		}
		else 
		{
			ystep = -1;
		};

		 for (int x=x0;x<x1;x++)
		 {
			 if (steep)
			 {
				 setPixel(y,x, color);
			 }
			 else 
			 {
				 setPixel(x,y, color);
			 }
			 error = error - deltay;
			 if( error < 0) 
			 {
				 y = y + ystep;
				 error = error + deltax;
			 }

		 }
	};

	unsigned int DecodeColor(const Str &style)
	{
		if (style.find("rgba")!=NOT_FOUND)
		{
			int Res[4]={0,0,0,0};
			float AlphaRes=0;
			int current = 0;
			
			int val = 0;
			bool afterdot = false;
			int digitsafterdot = 0;
			char *d = (char * ) (style.ptr());
			for (;*d;d++)
			{
				if (*d>='0' && *d<='9') 
				{
					if (current<3)
					{
						Res[current] *= 10;
						Res[current] += (*d-'0');
					}
					else
					{
						AlphaRes *= 10;
						AlphaRes += (*d-'0');
						if (afterdot) digitsafterdot++;
					}
				}
				else
				{
					if (*d ==',')
					{
						current ++;
						if (current == 4)break;
						
					}
					if (current == 3 && *d == '.')
					{
						afterdot = true;
					}
				}
			}
			while (digitsafterdot >0) { AlphaRes /= 10;digitsafterdot--;};
			unsigned int color = (Res[0]<<16) + (Res[1]<<8) + Res[2] + ((int)(AlphaRes*255.0f)<<24);
			return color;
		}
		else if (style.find("#")!=NOT_FOUND)
		{
		}
		else if (style.find("rgb")!=NOT_FOUND)
		{
			int Res[4]={0,0,0,0};
			int current = 0;
			int mul = 100;
			int val = 0;
			char *d = (char * ) (style.ptr());
			for (;*d;d++)
			{
				if (*d>='0' && *d<='9') 
				{
					Res[current] += mul * (*d-'0');
					mul = mul/10;
				}
				else
				{
					if (*d ==',')
					{
						current ++;
						if (current == 3)break;
						mul = 100;
					}
				}
			}
			unsigned int color = (Res[0]<<16) + (Res[1]<<8) + Res[2] + (0xff<<24);
			return color;
		};
		return 0;
	};

	o3_set void fillStyle(const Str &style)
	{
		m_renderstates[m_renderstates.size()-1].FillColor = DecodeColor(style);
	};

	o3_set void strokeStyle(const Str &style)
	{
		m_renderstates[m_renderstates.size()-1].StrokeColor = DecodeColor(style);
	};

	o3_set void strokeWidth (float Width)
	{
		m_renderstates[m_renderstates.size()-1].StrokeWidth = Width;
	};

	o3_fun void fillRect(float xx, float yy, float ww, float hh)
	{
		unsigned int color =  m_renderstates[m_renderstates.size()-1].FillColor;
		rect(xx,yy,ww,hh,color);
	};

	void SetupRenderState()
	{
		RenderState RS;
		RS.FillColor = 0xff000000;
		RS.StrokeColor = 0xff000000;
		m_renderstates.push(RS);
	};

	o3_fun void moveTo(float x, float y)
	{
		m_paths.push(Path());
		V2<float> point(x,y);
		m_paths[m_paths.size()-1].m_path.push(point);
		m_lastpoint.x = x;
		m_lastpoint.y = y;
	}

	o3_fun void lineTo(float x, float y)
	{
		if (m_paths.size() == 0)
		{
			m_paths.push(Path());
			m_paths[m_paths.size()-1].m_path.push(m_lastpoint);
		};
		V2<float> point(x,y);
		m_paths[m_paths.size()-1].m_path.push(point);
		m_lastpoint.x = x;
		m_lastpoint.y = y;
	};
	
	o3_fun void closePath()
	{
		if (m_paths.size() == 0) return;
		if (m_paths[0].m_path.size()<2) return;

		V2<float> first;
		first.x = m_paths[m_paths.size()-1].m_path[0].x;
		first.y = m_paths[m_paths.size()-1].m_path[0].y;

		m_paths[m_paths.size()-1].m_path.push(first);
		m_lastpoint = first;
	}

	o3_fun void beginPath()
	{
		m_paths.clear();
	}
	
	o3_fun void stroke()
	{
		unsigned int color = m_renderstates[m_renderstates.size()-1].StrokeColor;
		for (size_t i =0 ;i<m_paths.size();i++)
		{
			if (m_paths[i].m_path.size()>1)
			{
				V2<float> Prev = m_paths[i].m_path[0];
				for (size_t j = 1;j<m_paths[i].m_path.size();j++)
				{
					V2<float> Cur;
					Cur.x = m_paths[i].m_path[j].x;
					Cur.y = m_paths[i].m_path[j].y;
					line(Prev.x, Prev.y, Cur.x, Cur.y, color);
					Prev.x = Cur.x;
					Prev.y = Cur.y;
				};
			};
		};
		m_paths.clear();
	}


	class QuadraticCurveGen
	{
    public:
	    enum curve_recursion_limit_e { curve_recursion_limit = 32 };
		
		__inline double calc_sq_distance(double x1, double y1, double x2, double y2)
		{
			double dx = x2-x1;
			double dy = y2-y1;
			return dx * dx + dy * dy;
		}

        QuadraticCurveGen() : 
            m_approximation_scale(1.0),
            m_angle_tolerance(0.0),
            m_count(0)
        {}

        QuadraticCurveGen(double x1, double y1, 
                   double x2, double y2, 
                   double x3, double y3) :
            m_approximation_scale(1.0),
            m_angle_tolerance(0.0),
            m_count(0)
        { 
            init(x1, y1, x2, y2, x3, y3);
        }

        void reset() { m_points.clear(); m_count = 0; }
        void init(double x1, double y1, 
                  double x2, double y2, 
                  double x3, double y3)
		{
	        m_points.clear();
		    m_distance_tolerance_square = 0.5 / m_approximation_scale;
	        m_distance_tolerance_square *= m_distance_tolerance_square;
			bezier(x1, y1, x2, y2, x3, y3);
			m_count = 0;
		};

        void rewind(unsigned)
        {
            m_count = 0;
        }
		
		enum 
		{
			path_cmd_undefined, 
			path_cmd_move_to,
			path_cmd_line_to,
			path_cmd_stop
		};

        unsigned vertex(double* x, double* y)
        {
            if(m_count >= m_points.size()) return path_cmd_stop;
            V2<float> &p = m_points[m_count++];
            *x = p.x;
            *y = p.y;
            return (m_count == 1) ? path_cmd_move_to : path_cmd_line_to;
        }

    private:
    void recursive_bezier(double x1, double y1, 
                                      double x2, double y2, 
                                      double x3, double y3,
                                      unsigned level)
    {
        if(level > curve_recursion_limit) 
        {
            return;
        }

        // Calculate all the mid-points of the line segments
        //----------------------
        double x12   = (x1 + x2) / 2;                
        double y12   = (y1 + y2) / 2;
        double x23   = (x2 + x3) / 2;
        double y23   = (y2 + y3) / 2;
        double x123  = (x12 + x23) / 2;
        double y123  = (y12 + y23) / 2;

        double dx = x3-x1;
        double dy = y3-y1;
        double d = fabs(((x2 - x3) * dy - (y2 - y3) * dx));
        double da;

        if(d > curve_collinearity_epsilon)
        { 
            // Regular case
            //-----------------
            if(d * d <= m_distance_tolerance_square * (dx*dx + dy*dy))
            {
                // If the curvature doesn't exceed the distance_tolerance value
                // we tend to finish subdivisions.
                //----------------------
                if(m_angle_tolerance < curve_angle_tolerance_epsilon)
                {
                    m_points.push(V2<float>(x123, y123));
                    return;
                }

                // Angle & Cusp Condition
                //----------------------
                da = fabs(atan2(y3 - y2, x3 - x2) - atan2(y2 - y1, x2 - x1));
                if(da >= pi) da = 2*pi - da;

                if(da < m_angle_tolerance)
                {
                    // Finally we can stop the recursion
                    //----------------------
                    m_points.push(V2<float>(x123, y123));
                    return;                 
                }
            }
        }
        else
        {
            // Collinear case
            //------------------
            da = dx*dx + dy*dy;
            if(da == 0)
            {
                d = calc_sq_distance(x1, y1, x2, y2);
            }
            else
            {
                d = ((x2 - x1)*dx + (y2 - y1)*dy) / da;
                if(d > 0 && d < 1)
                {
                    // Simple collinear case, 1---2---3
                    // We can leave just two endpoints
                    return;
                }
                     if(d <= 0) d = calc_sq_distance(x2, y2, x1, y1);
                else if(d >= 1) d = calc_sq_distance(x2, y2, x3, y3);
                else            d = calc_sq_distance(x2, y2, x1 + d*dx, y1 + d*dy);
            }
            if(d < m_distance_tolerance_square)
            {
                m_points.push(V2<float>(x2, y2));
                return;
            }
        }

        // Continue subdivision
        //----------------------
        recursive_bezier(x1, y1, x12, y12, x123, y123, level + 1); 
        recursive_bezier(x123, y123, x23, y23, x3, y3, level + 1); 
    }

    //------------------------------------------------------------------------
    void bezier(double x1, double y1, 
                            double x2, double y2, 
                            double x3, double y3)
    {
        //m_points.add(V2<float>(x1, y1));
        recursive_bezier(x1, y1, x2, y2, x3, y3, 0);
        m_points.push(V2<float>(x3, y3));
    }




        double               m_approximation_scale;
        double               m_distance_tolerance_square;
        double               m_angle_tolerance;
        unsigned             m_count;
        tVec<V2<float> > m_points;
	};

	o3_fun void quadraticCurveTo(double cp1x, double cp1y, double x0, double y0)
	{
		QuadraticCurveGen Gen(m_lastpoint.x,m_lastpoint.y, cp1x, cp1y, x0, y0);
		double x, y;

		if (m_paths.size() == 0)
		{
			m_paths.push(Path());
			m_paths[m_paths.size()-1].m_path.push(m_lastpoint);
		};


		while (Gen.vertex(&x,&y) != QuadraticCurveGen::path_cmd_stop)
		{
			V2<float> point(x,y);
			m_paths[m_paths.size()-1].m_path.push(point);
		}

		m_lastpoint.x = x0;
		m_lastpoint.y = y0;

	};

//  // vector canvas API

// fillRect(x,y,w,h)
// clearRect(x,y,w,h)
// strokeRect(x,y,w,h)
// stroke();
// fill();
// arc(x,y,radius,startangle,endangle,anticlockwise);
// quadraticCurveTo(cp1x,cp1y,x,y);
// bezierCurveTo(cp1x,cp1y,cp2x,cp2y,x,y);
// clip();


	};
};

#endif // O3_C_IMAGE1_H
