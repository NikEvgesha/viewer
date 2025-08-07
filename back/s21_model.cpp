#include "s21_model.h"

namespace s21{

    void Model::move(double x_move, double y_move, double z_move, double x_turn, double y_turn, double z_turn, int zoom)
    {
        // qDebug() << "zzom = " << zoom;

        QMatrix4x4 transform;

        transform.translate(x_move, y_move, z_move);

        transform.rotate(x_turn, 1.0f, 0.0f, 0.0f);
        transform.rotate(y_turn, 0.0f, 1.0f, 0.0f);
        transform.rotate(z_turn, 0.0f, 0.0f, 1.0f);

        MovedV_.clear();

        for (QVector3D &vertex : V_) {
            MovedV_.push_back(transform * vertex);
        }

        V_=MovedV_;

        setScaleModel(zoom);
    }

    void Model::setScaleModel(float scale_){
        scale= scale_>0? scale*scale_ : scale/(-scale_);
    };

    void Model::setScaleToView(int viwer_height, int viewer_wight){
        /// поиск крайних вершин для масштаба
        float x_max(V_[0].x()), y_max(V_[0].y()), z_max(V_[0].z()), x_min(V_[0].x()), y_min(V_[0].y()), z_min(V_[0].z());
        for (QVector3D top : V_) {
            if (top.x()>x_max)
                x_max=top.x();
            if (top.y()>y_max)
                y_max=top.y();
            if (top.z()>z_max)
                z_max=top.z();

            if (top.x()<x_min)
                x_min=top.x();
            if (top.y()<y_min)
                y_min=top.y();
            if (top.z()<z_min)
                z_min=top.z();
        }

        float w_model = x_max - x_min;
        float h_model = y_max - y_min;

        float scale_y = (viwer_height) * 0.95 / h_model, scale_x = (viewer_wight) * 0.95 / w_model;

        scale = int(std::min({scale_x, scale_y}));

    };

    void Model::resetModel(){
        V_=V_start;
        F_=F_start;
        MovedV_.clear();
        scale=1;
    };
}
