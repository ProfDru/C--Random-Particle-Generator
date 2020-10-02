
namespace rpg {
class Registry {
 private:
  static int next_id;

  /*! \brief Get the next available ID */
  static int GetNextID();
};
}  // namespace rpg