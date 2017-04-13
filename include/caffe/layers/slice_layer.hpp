#ifndef CAFFE_SLICE_LAYER_HPP_
#define CAFFE_SLICE_LAYER_HPP_

#include <vector>

#include "caffe/blob.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"

namespace caffe {

/**
 * @brief Takes a Blob and slices it along either the num or channel dimension,
 *        outputting multiple sliced Blob results.
 *
 * TODO(dox): thorough documentation for Forward, Backward, and proto params.
 */
// 将一个输入 Blob 沿着它的 num 或 channel 维度对其进行分片，输出多个分片后的 Blob
template <typename Dtype>
class SliceLayer : public Layer<Dtype> {
 public:
  // 显示构造函数
  explicit SliceLayer(const LayerParameter& param)
      : Layer<Dtype>(param) {}
  // 层设置函数
  virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  // 层变形函数
  virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);

  virtual inline const char* type() const { return "Slice"; }
  virtual inline int ExactNumBottomBlobs() const { return 1; }
  virtual inline int MinTopBlobs() const { return 1; }

 protected:
  virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Forward_gpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
  virtual void Backward_gpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);

  int count_;
  int num_slices_; // 每类分片的数目
  int slice_size_; // 单位分片的尺寸
  int slice_axis_; // 执行分片的轴
  vector<int> slice_point_; // 分片的点
};

}  // namespace caffe

#endif  // CAFFE_SLICE_LAYER_HPP_
