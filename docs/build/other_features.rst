.. sectionauthor:: Jan-Willem Buurlage <janwillem@buurlagewits.nl>

.. highlight:: c

Other features
==============

There are two features we did not yet discuss. The first is timers, which are useful for getting information on the running time of your programs. The second is intervening in programs that are currently running on the Epiphany using the host.

Timers
------

We provide two mechanisms for getting running time information. The first uses the first timer (of the two) on the Epiphany core and is accurate for relatively short time intervals (less than about 7 seconds). It is used in the following manner::

    float t_start = bsp_time();
    // ... perform computation
    float t_end = bsp_time();
    float result = t_end - t_start;

The variable result than holds the time taken for the computation in seconds. If you want access to the number of clockcycles used for the computation we provide a similar function :ref:`ebsp_raw_time()<ebsp_raw_time>` which gives the number of clockcycles as an unsigned integer::

    unsigned int t_start = bsp_raw_time();
    // ... perform computation
    unsigned int t_end = bsp_raw_time();
    unsigned int result = t_end - t_start;

Note that the default Epiphany clockfrequency is about 600 MHz, such that 600000000 cycles is equal to one second.

Note that there are two separate timers available on the Epiphany cores, identified by ``E_CTIMER_0`` and ``E_CTIMER_1``. The Epiphany BSP library will only use ``E_CTIMRE_0`` so you are free to use the other timer in any way you require, using the Epiphany SDK.

The second method uses the system clock of the host to obtain the elapsed time. Because of varying amounts of latency this can be very inaccurate (its precision is in the order of milliseconds), but supports time intervals of arbitrary length. This timer can be used by calling the function ``ebsp_host_time()``::

    float t_start = ebsp_host_time();
    // ... perform (long) computation
    float t_end = ebsp_host_time();
    float result = t_end - t_start;

Interrupts
----------

It is possible to set up interrupt handlers using the Epiphany SDK functionality. The only interrupt that is explicitely and necessarily handled by the EBSP library is ``E_DMA1_INT``. For more information on the using the DMA engine, see the section on memory management. There is a timer interrupt that can be used if needed. The Epiphany BSP library uses neither of the two timre interrupts. The maximum number of cycles that can be counted using the raw timer is ``UINT_MAX`` which is roughly 7 seconds on the 600 MHz cores. After reaching this maximum value, an interrupt will be fired.

Callbacks
---------

If you want to use the host processor together with the Epiphany processor, you require some sort of syncing mechanism. In particular you might want to react to data that has been sent to external memory, or use the ARM in a map-reduce kind of setting. For this we provide a callback mechanism using ``ebsp_set_sync_callback``. You can provide a function pointer, and this function will get called each time a core calls ``ebsp_host_sync``::

    // on the host
    void callback() {
        printf("ebsp_host_sync called on the Epiphany");
        // communicate with cores or react to data
    }

    ..
    bsp_begin(bsp_nprocs());
    ebsp_set_sync_callback(callback);
    ..

Similarly we provide a callback mechanism for ``bsp_end``, which can be useful when developing your own library on top of EBSP.

Interface (Timer and callback)
------------------------------

Host
^^^^

.. doxygenfunction:: ebsp_set_sync_callback
   :project: ebsp_host

.. doxygenfunction:: ebsp_set_end_callback
   :project: ebsp_host

Epiphany
^^^^^^^^

.. doxygenfunction:: bsp_time
   :project: ebsp_e

.. _ebsp_raw_time:
.. doxygenfunction:: ebsp_raw_time
   :project: ebsp_e

.. doxygenfunction:: ebsp_host_time
   :project: ebsp_e
