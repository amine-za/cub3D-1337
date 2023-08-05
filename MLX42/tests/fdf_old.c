#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<mlx.h>

enum {
   ON_KEYDOWN = 2,
   ON_KEYUP = 3,
   ON_MOUSEDOWN = 4,
   ON_MOUSEUP = 5,
   ON_MOUSEMOVE = 6,
   ON_EXPOSE = 12,
   ON_DESTROY = 17
};

typedef struct s_data {
   void     *img;
   char     *addr;
   int      bits_per_pixel;
   int      line_length;
   int      endian;
}     t_data;

typedef struct v3 {
   float x;
   float y;
   float z;
}     vector3;

typedef struct  v2 {
   int    x;
   int    y;
}     vector2;

typedef struct  s_vars {
   vector2 **p;
   vector2 grid_start;
   vector2 grid_size;
   vector2  grid_shift;
   float grid_rot;
   void    *mlx;
   void    *win;
   t_data   *data;
}     t_vars;

void  my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
   char  *dst;

   dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
   *(unsigned int*)dst = color;
}

void  connect_pointsDDA(t_data *img, vector2 p1, vector2 p2)
{
   double x;
   double y;
   double dx;
   double dy;
   double s;
   int   i;

   x = p1.x;
   y = p1.y;
   dx = p2.x - p1.x;
   dy = p2.y - p1.y;
   s = dy/dx;
   if (abs(dx) >= abs(dy))
      s = abs(dx);
   else
      s = abs(dy);
   dx = dx / s;
   dy = dy / s;
   i = 1;
   while (i <= s)
   {
      my_mlx_pixel_put(img, x, y, 0x00FFFFFE);
      x = x + dx;
      y = y + dy;
      i++;
      //x++;
      //y = s * (x - p1.x)  + p1.y;
   }
   return ;
}

void    connect_points_low(t_data *img, vector2 p1, vector2 p2)
{
        double x;
        double y;
        double dx;
        double dy;
        double s;
        int i;

   dx = p2.x - p1.x;
   dy = p2.y - p1.y;
   i = 1;
   if (dy < 0)
   {
      i = -1;
      dy = -dy;
   }
   s = (2 * dx) - dy;
   x = p1.x;
   y = p1.y;
   while(x <= p2.x)
   {
      my_mlx_pixel_put(img, x, y, 0x00FFFFFE);
      if (s > 0)
      {
         y = y + i;
         s += 2 * (dy - dx);
      }
      else
         s += 2 * dy;
      x++;
   }
}

void    connect_points_high(t_data *img, vector2 p1, vector2 p2)
{
        double  x;
        double  y;
        double  dx;
        double  dy;
        double  s;
        int     i;

        dx = p2.x - p1.x;
        dy = p2.y - p1.y;
        i = 1;
        if (dx < 0)
        {
                i = -1;
                dx = -dx;
        }
        s = (2 * dy) - dx;
        x = p1.x;
        y = p1.y;
        while(y <= p2.y)
        {
                my_mlx_pixel_put(img, x, y, 0x00FFFFFE);
                if (s > 0)
                {
                        x = x + i;
                        s += 2 * (dx - dy);
                }
                else
         s += 2 * dx;
      
      y++;
        }
}

void    connect_points(t_data *img, vector2 p1, vector2 p2)
{
        if (abs(p2.y - p1.y) < abs(p2.x - p1.x))
        {
                if (p1.x > p2.x)
                        connect_points_low(img, p2, p1);
                else
                        connect_points_low(img, p1, p2);
        }
        else
        {
                if (p1.y > p2.y)
                        connect_points_high(img, p2, p1);
                else
                        connect_points_high(img, p1, p2);
        }
}

void  init_grid(t_vars *vars)
{
   vector2  ***p;
   int   i;
   int   j;
   vector3  p3;

   p3.x = vars->grid_start.x;
   p3.y = vars->grid_start.y;

   p = (vector2***) malloc(sizeof(vector2**));
   p[0] = (vector2**) malloc(vars->grid_size.x * sizeof(vector2*));
   i = -1;
   while (++i < vars->grid_size.x)
      p[0][i] = (vector2*) malloc(vars->grid_size.y * sizeof(vector2));
   //-------make_grid--------
   i = 0;
   j = 0;
   while (j < vars->grid_size.y)
   {
      p[0][i][j].x = p3.x;
      p[0][i][j].y = p3.y;
      p3.x += vars->grid_shift.x;
      p3.y +=  vars->grid_shift.y * vars->grid_rot;
      i++;
      if (i == vars->grid_size.x)
      {
         j++;
         i = 0;
         p3.x = vars->grid_start.x - (vars->grid_shift.x * j) * vars->grid_rot;
         p3.y = vars->grid_start.y + vars->grid_shift.y * j;
      }
   }
   p[0][2][1].y -= 20;
   p[0][2][2].y -= 20;
   p[0][3][1].y -= 20;
   p[0][3][2].y -= 20;

   vars->p = p[0];
}

int   draw_grid(t_vars *vars)
{
   int   i;
   int   j;

   i = 0;
        j = 0;
        while (j < vars->grid_size.y)
        {
                if (i < vars->grid_size.x -1)
                        connect_points(vars->data, vars->p[i][j], vars->p[i +1][j]);
                if (j < vars->grid_size.y -1) 
                        connect_points(vars->data, vars->p[i][j], vars->p[i][j +1]);
                i++;
                if (i == vars->grid_size.x)
                {
                        j++;
                        i = 0;
                }
        }
   return (0);
}

int     close(int keycode, t_vars *vars)
{
   //mlx_destroy_image(vars->mlx, vars->img);
        mlx_destroy_window(vars->mlx, vars->win);
        return (0);
}

int   mouse_hook(int mousecode, t_vars *vars)
{
   printf("hello mouse %d\n",mousecode);
   vars->grid_start.x += 1;
   return (1);
}

int   render_add_grid(t_vars *vars)
{
   static int x;

   //printf(".");
   vars->data->img = mlx_new_image(vars->mlx, 720, 480);
   vars->data->addr = mlx_get_data_addr(vars->data->img, &vars->data->bits_per_pixel, &vars->data->line_length, &vars->data->endian);  

   mlx_mouse_hook(vars->win, mouse_hook, vars);
   vars->grid_start.x--;
   //vars->grid_size.x++;

   init_grid(vars);
   draw_grid(vars);

   mlx_put_image_to_window(vars->mlx, vars->win,vars->data->img, 0, 0);
   return (0);
}

int   render_remove_grid(t_vars *vars)
{
   static int x;

   //printf(".");
   vars->data->img = mlx_new_image(vars->mlx, 720, 480);
   vars->data->addr = mlx_get_data_addr(vars->data->img, &vars->data->bits_per_pixel, &vars->data->line_length, &vars->data->endian);  

   mlx_mouse_hook(vars->win, mouse_hook, vars);
   vars->grid_start.x--;
   vars->grid_size.x--;

   //vars->grid_rot -= 0.01;
   //if (vars->grid_rot < -0.3)
   // vars->grid_rot = 1;

   init_grid(vars);
   draw_grid(vars);

   mlx_put_image_to_window(vars->mlx, vars->win,vars->data->img, 0, 0);
   return (0);
}

void fdf()
{
   t_vars   *vars;
   int   z;
   
   printf ("hello... a tle9 sloka\n");
   vars =(t_vars *) malloc(2 * sizeof(t_vars));
   vars->mlx = mlx_init();
   vars->win = mlx_new_window(vars->mlx, 720, 480, "sloka d l7did");
   
   vars->data =(t_data *) malloc(2 * sizeof(t_data));
   vars->data->img = mlx_new_image(vars->mlx, 720, 480);
   vars->data->addr = mlx_get_data_addr(vars->data->img, &vars->data->bits_per_pixel, &vars->data->line_length, &vars->data->endian);
   
   vars->grid_size.x = 10;
   vars->grid_size.y = 10;
   vars->grid_start.x = 300;
        vars->grid_start.y = 50;
        vars->grid_shift.x = 37;
        vars->grid_shift.y = 13;
   vars->grid_rot = 1;

   init_grid(vars);
   draw_grid(vars);


   //i=0 i=1   i=2      k
   //.    .  . .  .  j=0
   //       
   //     .  . .  .  .  j=1
   //
   //        . .  .  .  .  j=2
   //
   //          .  .  .  .  
   int i = 0;
   int j = 0;
   int k = vars->grid_size.x -1;
   while (i++ < k && j < k)
   {
      my_mlx_pixel_put(vars->data, vars->p[i][j].x, vars->p[i][j].y, 0x00FF0000);
      if (i == k)
      {
         i = 0;
         j++;
      }
   }

   printf("render");
   mlx_put_image_to_window(vars->mlx, vars->win,vars->data->img, 0, 0);
   mlx_hook(vars->win, 2, 1L<<0, close, vars);
   mlx_hook(vars->win, ON_DESTROY, 0, close, vars);
   mlx_loop_hook(vars->mlx, render_add_grid, vars);
   //mlx_loop_hook(vars->mlx, render_remove_grid, vars); 
   //mlx_loop_hook(vars, draw_grid, vars);
   mlx_loop(vars->mlx);
}

int main()
{
   fdf();
   return 0;
}
int main()
{
   void  *mlx;
   void  *mlx_win;
   t_data  img;

   mlx = mlx_init();
   mlx_win = mlx_new_window(mlx,720, 480, "Hello");
   img.img = mlx_new_image(mlx, 720, 480);
   img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
   int x = 10;
   int y = 10; 
   while (y < 200)
   {
      x = y;
      while (x < 200)
      {
	      my_mlx_pixel_put(&img, x, y, 0x00FF0000);
         x++;
      }
      y++;
   }
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
   mlx_loop(mlx);
}