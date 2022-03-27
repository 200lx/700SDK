/* SCCS info:   Module xbs_inte.h  Version 1.1  Date 11/09/93  Time 15:26:32 */

/*SC_XBS_UNIQUE   */
#ifndef XBS_inter.h


#define SC_XBS_GET_VIEW_PTR	(SC_XBS_UNIQUE	  * 256) + 0 + FNCT_BASE
#define _m_get_view_ptr proc  ()			       \
	c_service_far_ptr(SC_XBS_GET_VIEW_PTR  )

#define SC_XBS_SET_VIEW		(SC_XBS_UNIQUE	  * 256) + 1 + FNCT_BASE
#define _m_get_view	  \
	c_service(SC_XBS_SET_VIEW ,(void far *)(a))

#define SC_XBS_CLEAR_VIEWS	(SC_XBS_UNIQUE	  * 256) + 2 + FNCT_BASE
	_m_clear_all_views( a)
	c_service(SC_XBS_CLEAR_VIEWS  ,(int) (a))

#endif /* XBS_inter.h */
