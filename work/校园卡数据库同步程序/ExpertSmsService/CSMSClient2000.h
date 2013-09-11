// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

// CSMSClient2000 wrapper class

class CSMSClient2000 : public COleDispatchDriver
{
public:
	CSMSClient2000(){} // Calls COleDispatchDriver default constructor
	CSMSClient2000(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CSMSClient2000(const CSMSClient2000& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ISMSClient2000 methods
public:
	VARIANT OpenSMS(VARIANT mServer, VARIANT mPort)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &mServer, &mPort);
		return result;
	}
	VARIANT SendSMS(VARIANT mRecord, VARIANT mMobile, VARIANT mContent)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &mRecord, &mMobile, &mContent);
		return result;
	}
	VARIANT CloseSMS()
	{
		VARIANT result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT get_Error()
	{
		VARIANT result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT ReadSMS()
	{
		VARIANT result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT get_Option()
	{
		VARIANT result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT get_Record()
	{
		VARIANT result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT get_Mobile()
	{
		VARIANT result;
		InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT get_Content()
	{
		VARIANT result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT get_DateTime()
	{
		VARIANT result;
		InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}

	// ISMSClient2000 properties
public:

};
