/*
 * main.c
 *
 *  Created on: 2023 Dec 12 11:41:41
 *  Author: remzz
 */




#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)

/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */
      uint32_t new_baudrate = 1000000;  // in Hz
      uint16_t new_sampe_point = 80;
      uint8_t new_sjw = 2;


int main(void)
{
  DAVE_STATUS_t status;
        uint8_t can_data_arr[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
        uint8_t *array_data;
  status = DAVE_Init();           /* Initialization of DAVE APPs  */
  const CAN_NODE_t *HandlePtr1 = &CAN_NODE_0;
       XMC_CAN_MO_t *MO_Ptr;

       MO_Ptr = HandlePtr1->lmobj_ptr[0]->mo_ptr;   //'0' refers to first message object configured
                                                     // for the selected can node
  if(status != DAVE_STATUS_SUCCESS)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
    XMC_DEBUG("DAVE APPs initialization failed\n");

    while(1U)
    {

    }
  }

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {          //can transmit code
	         // For run time baud rate configuration change
	         // Configure new baud rate to 1MHz

	         XMC_CAN_NODE_SetInitBit(HandlePtr1->node_ptr);

	         CAN_NODE_ConfigBaudrate(HandlePtr1, new_baudrate, new_sampe_point,new_sjw);

	         XMC_CAN_NODE_ResetInitBit(HandlePtr1->node_ptr);


	          MO_Ptr->can_mo_type = XMC_CAN_MO_TYPE_TRANSMSGOBJ;  //Configure message object type as transmit type
	          MO_Ptr->can_id_mode = XMC_CAN_FRAME_TYPE_STANDARD_11BITS; //configure MO identifier type
	          MO_Ptr->can_data_length = 8; // Configure CAN transmit MO data length field
	          MO_Ptr->can_data[1] = 0xAAAA5555;  // Configure Higher 4 bytes of Data
	          MO_Ptr->can_data[0] = 0xAAAA5555;  // Configure Lower 4 bytes of Data
	          // Runtime change the MO configuration
	          CAN_NODE_MO_Init(HandlePtr1->lmobj_ptr[0]);

	          array_data = can_data_arr;
	          CAN_NODE_MO_UpdateData(HandlePtr1->lmobj_ptr[0],array_data); //  update data for the MO to transmit
	          for(int i=0;i<900000;i++);
	          CAN_NODE_MO_Transmit(HandlePtr1->lmobj_ptr[0]);  // transmit the data


	          //can receive code

	          CAN_NODE_MO_Receive(HandlePtr1->lmobj_ptr[0]); // Read the received Message object
	          CAN_NODE_MO_ReceiveData(HandlePtr1->lmobj_ptr[0]); // Read the received Message object



  }
}
