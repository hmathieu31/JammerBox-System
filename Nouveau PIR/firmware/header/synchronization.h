/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  Sychronization	                                     */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  18.09.2012                                             */
/* Author          :  Christian Ringlstetter/Thomas Pichler                  */
/*****************************************************************************/

#ifndef _SYNCHRONIZATION_H_
#define _SYNCHRONIZATION_H_

//### CRK Synchronisation Function ###	
	
	void sync_CRK(void); 

//### CAM_CRK Synchronisation Function ###
	
	void sync_CAM_CRK (int); 

//### Stalling Detection Function ###

	void Stalling_detection(void);

//### CRK Stalling Detection Function ###

	void Stalling_detection_CRK(void);
//### CAM Stalling Detection Function ###

	void Stalling_detection_CAM(int);    
    
    
// ## CRK synchronisation preparation

	void sync_CRK_preparation(void); 

// ## CAM_CRK synchronisation preparation

	void sync_CAM_CRK_preparation (void); 

// ## Gap to edge calculation

	void gap_to_edge_calculation(void);

// ## Reset CAM_CRK_synch

	void CAM_CRK_synch_reset(int);

// ## Reset CAM_CRK_synch_ahead

	void CAM_CRK_synch_ahead_reset(int);

// ## Set CAM_CRK_synch

	void CAM_CRK_synch_set(int);

// ## IC overflow check

	void IC_overflow_check();


#endif
/*****************************************************************************/
/*****************************************************************************/

