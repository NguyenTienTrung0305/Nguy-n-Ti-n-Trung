#ifndef TIMERFPS_H
#define TIMERFPS_H


class Timerfps
{
    public:
        Timerfps();
        virtual ~Timerfps();

        void start();
        void stop();
        void paused();
        void unpaused();

        int get_tick(); // lay ra thoi gian

        bool is_started();
        bool is_paused();

    protected:

    private:
        int start_tick_; // thoi diem bat dau chay
        int paused_tick_; // thoi diem tam dung

        bool is_paused_;
        bool is_started_;

};

#endif // TIMERFPS_H
