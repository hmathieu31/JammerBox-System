/*****************************************************************************/
/* Projectname     :  ENSD-Jammer                                            */
/* Programm        :  Failures			                                     */
/* Controller      :  dsPIC33F                                               */
/* Latest change   :  31.08.2020                                             */
/* Author          :  Grégoire Chabin/Christian Ringlstetter/Thomas Pichler  */
/*****************************************************************************/

#ifndef _FAILURES_H_
#define _FAILURES_H_

//### Output_CRK Function in case of no failure ###

	void Output_CRK_no_failure(void);

//### Output_CAM Function in case of no failure ###

	void Output_CAM_no_failure(int);

//### Output_CRK Function ###

	void Output_CRK(char);

//### Output_CAM Function ###

	void Output_CAM(char ,int);

//### Failure Processing ###

	void Failure_processing(char);

//### CRK_RUN_OUT ###
	
	void CRK_RUN_OUT(void);

//### Output CRK_RUN_OUT ###
 	
	void Output_CRK_RUN_OUT(void);

//### CRK_RUN_OUT_reset ###

	void CRK_RUN_OUT_reset(void);

//## Output CAM: CAM_PER

	void Output_CAM_PER(int);

//## CAM_PER_reset

	void CAM_PER_reset(void);

//## Output CRK: CAM_CRK_TOOTH_PER

	void Output_CRK_TOOTH_PER(void);

//## CRK_TOOTH_PER

	void CRK_TOOTH_PER(void);

//## CRK_TOOTH_PER_reset
	void CRK_TOOTH_PER_reset(void);

     
//## Output_CRK_TOOTH_OFF

    void Output_CRK_TOOTH_OFF(void);

//## CRK_TOOTH_OFF_reset
    
    void CRK_TOOTH_OFF_reset(void);
   
    
//## Output_CRK_GAP_NOT_DET
    
    void Output_CRK_GAP_NOT_DET(void);

//## CRK_GAP_NOT_DET_reset
    
    void CRK_GAP_NOT_DET_reset(void); 
    
    
//## Output_SEG_ADP_ER_LIM
    
    void Output_SEG_ADP_ER_LIM(void);

//## SEG_ADP_ER_LIM_reset
    
    void SEG_ADP_ER_LIM_reset(void); 
    
    
//## Output_CRK_PLS_ORNG
    
    void Output_CRK_pulse_duration(void);

//## CRK_PLS_ORNG_reset
    
    void CRK_pulse_duration_reset(void); 
    
    
//## Output_POSN_ENG_STST
    
    void Output_POSN_ENG_STST(void);

//## POSN_ENG_STST_reset
    
    void POSN_ENG_STST_reset(void);     
    
//## Output_SC_CAM_CRK
    
    void Output_SC_CAM_CRK(int);

//## SC_CAM_CRK_reset
    
    void SC_CAM_CRK_reset(void);  
    
 //## Output_CAM_PAT_ERR    
    
    void Output_CAM_PAT_ERR(int);
    
 //## CAM_PAT_ERR_reset   
    
    void CAM_PAT_ERR_reset();
    
    
//## Output CAM_delay: CAM_TOOTH_OFF / CAM_REF_CRK / CAM_SYN / CAM_SYN_CRK

	void Output_CAM_delay (int);
	
//## CAM_delay: CAM_TOOTH_OFF / CAM_REF_CRK / CAM_SYN / CAM_SYN_CRK

	void CAM_delay (int);

//## CAM_delay_counter: CAM_TOOTH_OFF / CAM_REF_CRK / CAM_SYN / CAM_SYN_CRK
	
	void CAM_delay_counter(int);

//## CAM_delay reset

	void CAM_delay_reset (void);

//### Failure Reset ###

	void Failure_reset(void);

//### Failure Synchronization Reset ###

	void Failure_synch_reset(char);

//### Former teeth time calculation ###

	double Former_teeth_time_calculation(long, unsigned int, int);

//### Former teeth time calculation output ###

	double Former_teeth_time_calculation_output(long, unsigned int, int);

#endif
/*****************************************************************************/
/*****************************************************************************/


