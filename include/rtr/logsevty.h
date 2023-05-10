#ifndef _rtr_logsevty_h 
#define _rtr_logsevty_h

class RTRLogSeverity
{
public:
	enum SeverityLevel { 
				all_severity, 
				debug, 
				info,
				notice, 
				warning, 
				error, 
				critical, 
				alert, 
				emergency};
		// The severity level

protected:
	inline RTRLogSeverity() {};
	inline ~RTRLogSeverity() {};
};

#endif
