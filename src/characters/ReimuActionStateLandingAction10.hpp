// Shared target landing tail for actions202/203/225/226 at47AE4A.
// Include once per staging method; the label denotes actual incoming edges.
reimu_landed_action_10:
            zero_velocity_acceleration();
            y_f0 = reimu_stage_surface_height_at_x(this);
            set_action(10);
            return true;
