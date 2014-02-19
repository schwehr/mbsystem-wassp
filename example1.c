/* standard include files */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* MBIO include files */
#include "mb_status.h"
#include "mb_define.h"
#include "mb_io.h"


int main (int argc, char **argv)
{
	extern char *optarg;
	// int	errflg = 0;
	// int	c;
	// int	help = 0;
	// int	flag = 0;

	/* MBIO status variables */
	// int	status = MB_SUCCESS;
	int	verbose = 0;
	int	error = MB_ERROR_NO_ERROR;
	char	*message;

	/* MBIO read control parameters */
	int	format;
	int	pings;
	int	lonflip;
	double	bounds[4];
	int	btime_i[7];
	int	etime_i[7];
	double	btime_d;
	double	etime_d;
	double	speedmin;
	double	timegap;
	mb_path	file="stdio";
	int	pings_get = 1;
	int	beams_bath_alloc = 0;
	int	beams_amp_alloc = 0;
	int	pixels_ss_alloc = 0;

	/* MBIO read values */
	void	*mbio_ptr = NULL;
	int	kind;
	int	time_i[7];
	double	time_d;
	double	navlon;
	double	navlat;
	double	speed;
	double	heading;
	double	distance;
	double	altitude;
	double	sonardepth;
	int	beams_bath = 0;
	int	beams_amp = 0;
	int	pixels_ss = 0;
	char	*beamflag = NULL;
	double	*bath = NULL;
	double	*bathlon = NULL;
	double	*bathlat = NULL;
	double	*amp = NULL;
	double	*ss = NULL;
	double	*sslon = NULL;
	double	*sslat = NULL;
	char	comment[MB_COMMENT_MAXLINE];
         
	/* get current default values */
        if (MB_SUCCESS != mb_defaults(verbose,&format,&pings_get,&lonflip,bounds,
                                      btime_i,etime_i,&speedmin,&timegap)) {
          mb_error(verbose,error,&message);
          fprintf(stderr,"\nMBIO Error returned from function <mb_defaults>:\n%s\n",message);
          fprintf(stderr,"\nProgram Terminated\n");
          exit(error);  // Or we could use EXIT_FAILURE
        }

        // strcpy (file, "stdin");

	/* process argument list */
        {
          int c=0, flag=0, errflg=0;
	  while ((c = getopt(argc, argv, "F:f:I:i:")) != -1)
	  switch (c)
            {
            case 'F':
            case 'f': // fall through
              sscanf (optarg,"%d", &format);
              flag++;
              break;
            case 'I':
            case 'i': // fall through
              sscanf (optarg,"%s", file);
              flag++;
              break;
            case '?':
              errflg++;
            default:
              fprintf(stderr, "ERROR: unknown getopt case: %c\n", c);
            }
          // TODO: Do something if errflg is true.
        }

	/* initialize reading the swath file */
	if (mb_read_init(
		verbose,file,format,pings_get,lonflip,bounds,
		btime_i,etime_i,speedmin,timegap,
		&mbio_ptr,&btime_d,&etime_d,
		&beams_bath_alloc,
		&beams_amp_alloc,
		&pixels_ss_alloc,
		&error) != MB_SUCCESS)
          {
            mb_error(verbose,error,&message);
            fprintf(stderr,"\nMBIO Error returned from function <mb_read_init>:\n%s\n",message);
            fprintf(stderr,"\nSwath File <%s> not initialized for reading\n",file);
            fprintf(stderr,"\nProgram Terminated\n");
            exit(error);
          }

	/* allocate memory for data arrays */
        // TODO: These should all trigger exit if they fail to register.

        mb_register_array(verbose, mbio_ptr, MB_MEM_TYPE_BATHYMETRY,
                                        sizeof(char), (void **)&beamflag, &error);
        if (error == MB_ERROR_NO_ERROR)
            mb_register_array(verbose, mbio_ptr, MB_MEM_TYPE_BATHYMETRY,
                              sizeof(double), (void **)&bath, &error);
        if (error == MB_ERROR_NO_ERROR)
            mb_register_array(verbose, mbio_ptr, MB_MEM_TYPE_AMPLITUDE,
                              sizeof(double), (void **)&amp, &error);
        if (error == MB_ERROR_NO_ERROR)
            mb_register_array(verbose, mbio_ptr, MB_MEM_TYPE_BATHYMETRY,
                              sizeof(double), (void **)&bathlon, &error);
        if (error == MB_ERROR_NO_ERROR)
            mb_register_array(verbose, mbio_ptr, MB_MEM_TYPE_BATHYMETRY,
                              sizeof(double), (void **)&bathlat, &error);
        if (error == MB_ERROR_NO_ERROR)
            mb_register_array(verbose, mbio_ptr, MB_MEM_TYPE_SIDESCAN,
                              sizeof(double), (void **)&ss, &error);
        if (error == MB_ERROR_NO_ERROR)
            mb_register_array(verbose, mbio_ptr, MB_MEM_TYPE_SIDESCAN,
                              sizeof(double), (void **)&sslon, &error);
        if (error == MB_ERROR_NO_ERROR)
            mb_register_array(verbose, mbio_ptr, MB_MEM_TYPE_SIDESCAN,
                              sizeof(double), (void **)&sslat, &error);

	/* read and process data */
        // Errors less than 0 are not fatal.
	while (error <= MB_ERROR_NO_ERROR) {
          /* read a ping of data */
          /* status = */
          mb_read(verbose, mbio_ptr, &kind, &pings, 
                  time_i, &time_d, 
                                 &navlon, &navlat, 
                                 &speed, &heading, 
                                 &distance, &altitude, &sonardepth, 
                                 &beams_bath, &beams_amp, &pixels_ss, 
                                 beamflag, bath, amp, 
                                 bathlon, bathlat, 
                                 ss, sslon, sslat, 
                           comment, &error);
                
          fprintf(stdout, "%f %f %f\n",time_d,navlon,navlat);
        }

	/* status = */ mb_close(verbose, &mbio_ptr, &error);
        /* status = */ mb_memory_list(verbose,&error);

        return EXIT_SUCCESS;
}

                
                

                                        
                                        
                                        
